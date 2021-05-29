﻿// © Copyright 2021 Ongakken s.r.o. All rights reserved.
//   Ongakken, the alternative names オンガッケン, オンがッけン, the Ongakken logo, the Ongakken symbol, the Ongakken pattern are trademarks of Ongakken s.r.o.

#pragma once // include this file (and any files that reference this header file) exactly once in the compilation. Compile exactly once.

#include <unistd.h> // cinlude the standard POSIX sys lib
#include <iostream> // standard C++ I/O stream lib, needed for stuff like cout and cin
#include <fstream> // standard C++ file stream lib, needed for loading, reading writing to or otherwise manipulating files
#include <time.h> // C lib used for nanosleep(2); nanosleep() is obsolete and thus we're switching to nanosleep(2) instead
#include <stdlib.h>
#include <limits.h>
#include <cstring>

class host // this class is the base class for all the individual in-game machines which the player will have access to
{
public:
	void spawnShell(host& Host);
	int evaluateCmdInput(std::string cmdInputUnprocessed); // this method  takes the command input from the player and checks if that command literal exists; if it does, it runs it, if not, it throws a printf error
	std::string hostname;
	std::string IPaddr;
	std::string cmdInput; // command input the player will enter while having access to an interactive shell - this value will be processed and evaluated to see if the command entered exists
	std::string cmdArgInput; // a string for args of the commands entered into the string declared above
	int openPorts[10];
	int closedPorts[10];
	bool bInteractiveShell; // allow the player to access the in-game shell? if true, a while loop will run and the player will have access to the shell
};

class user // this base class will handle all usable users within the game, incl. the player's user, 'j3ff'
{
public:
	int uid;
	std::string username;
};

class root : public user // this subclass is the root users class and will have some special, root-only methods available
{
	int uid = 0; // superuser's UID is always 0
private:
	// private properties

	// private methods
	int purge(); // once the player gains access to a root shell, they can invoke the 'purge' custom script whose functionality will be defined by this method. It'll essentially remove all file objects from the current machine
};

class file // this is how we'll interact with files
{
public:
	// remember that Linux is case-sensitive
	std::string absPath; // the absolute path to a regular file or directory, e.g. /home/simtoon/. When dealing with a directory, the abs. path stands for the location of the dir, so if the dir is Desktop, then /home/simtoon means that the dir is in /home/simtoon/Desktop
	int perms; // Unix-defined permissions notation in the int format, e.g. 755, 700, 777 or whatever. Prototype: owner:group:others
	std::string owner; // ls -l, file owner
	bool isDev; // is this file a device? notice that we only differentiate between regular files and dirs - we do not need special files, sockets, or symlinks in this game
};

class directory : public file // this class is a child class of file because everything in Linux is a file under the hood, including directories
{
public:
	std::string absPath; // the absolute path of this dir, e.g. /var/log
	bool canList;
	bool canAccess;
};

class core
{
public: //I know, I know, encapsulation ... well, in this case, it isn't exactly neccesarry, so I won't do it. Maybe later.
	////////// core vars and methods that run the game itself //////////

	//// vars
	std::string gameVersion;
	std::string playerMsg; // a string to be iterated over using the iterateOverString method. when passed, the method will emulate actual human-like typing, thus indicating to the player that they are 'typing'

	//// methods
	void init(); // this method checks the runtime dependencies and verifies if all dirs exist; if not, it creates them. we also play the intro seq here
	void boot(); // this method runs the simulated boot seq of the in-game computer
	void lvl1(); // level methods -- these run code relevant for each level of the game
	void lvl2(host& J3ff);
	void iterateOverString(std::string& playerMsg, int s, int long ns); // a method to iterate through a "msg" string and print out characters divided by an 's' amount of sleep (in seconds)

	////////////////////////////////////////////////////////////////////


	////////// command methods - methods that will execute stuff based on what shell command they represent //////////

	int help(); // this method prints the TermOS help table to assist the players in navigating the game. a lot like an actual manual for a game, but considerably more confusing
	int ls();
	int cd(directory dir);
	int cp(file file, directory dir);
	int scp(file file, directory dir);
	int rm(file file);
	int scan();
	int ifconfig();
	int iwconfig();
	int whoami(const char* arg = ""); // this func finds the user name associated with the currect effective userid. we're passing a default input of "" so it works even when called like whoami();
	int uptime();
	int lshw(host host);
	int nmap(std::string IPaddr, std::string mask);
	int set_target(host target); // TODO: implement a TAB filling functionality
	int execute();
	int poweroff();
	int lsgameinfo();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};