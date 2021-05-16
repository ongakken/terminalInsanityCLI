// © Copyright 2021 Ongakken s.r.o. All rights reserved.
//   Ongakken, the alternative names オンガッケン, オンがッけン, the Ongakken logo, the Ongakken symbol, the Ongakken pattern are trademarks of Ongakken s.r.o.

#pragma once //include this file (and any files that reference this header file) exactly once in the compilation

using namespace std; //standard namespace for using cout, cin and some other without defining the namespace they're in (std::cout)

#ifdef _WIN32 //is the current platform Windows? load the system lib
#include <Windows.h>
#else //are we on anything else? load the POSIX unix sys lib
#include <unistd.h>
#endif
//#include <cstdio> //we don't really need this lib right now, but keeping it here just in case. I mean, there's gotta be a reason why I put it in in the first place, right? xD
#include <iostream> //standard C++ I/O stream lib, needed for stuff like cout and cin
#include <fstream> //standard C++ file stream lib, needed for loading, reading writing to or otherwise manipulating files


class core
{
public:
	////////// core vars and methods that run the game itself //////////

	//// vars
	int init(); // this method checks the runtime dependencies and verifies if all dirs are existing; if not, it creates them. we also play the intro seq here
	int boot(); // this method runs the simulated boot seq of the in-game computer
	int lvl1(); // level methods -- these run code relevant for each level of the game
	string cmdInput; // command input the player will enter while having access to an interactive shell - this value will be processed and evaluated to see if the command entered exists
	string playerMsg; // a string to be iterated over using the iterateOverString method. when passed, the method will emulate actual human-like typing, thus indicating to the player that they are 'typing'

	//// methods
	void iterateOverString(string &playerMsg, int s); // a method to iterate through a "msg" string and print out characters divided by an 's' amount of sleep (in seconds)
	void evaluateCmdInput(const char* cmdInputChar); // this method  takes the command input from the player and checks if that command literal exists; if it does, it runs it, if not, it throws a printf error

	////////////////////////////////////////////////////////////////////


	////////// command methods - methods that will execute stuff based on what shell command they represent //////////

	int whoami();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};



