/*  © Copyright 2021 - 2022 Ongakken s.r.o. (Slovakia) and Simtoon Underholdning (Denmark) - All rights reserved.
	Terminal Insanity, Ongakken, the alternative names オンガッケン,  オンがッけン,
	the Ongakken logo, the Ongakken symbol, the Ongakken pattern are trademarks of Ongakken s.r.o.
	Based on a 2016 videogame 'Terminal Insanity' by Simon Slamka

	this source file includes comments other than those that you would expect in a software project
	since I am writing this as a single developer with no foreseeable collaboration, I allowed myself to use this as a diary
	I did something similar with "Imaginator", a game I worked on a couple of years ago
*/

#include "main.h"

uint64_t constexpr mix(char m, uint64_t s) // credit to @aleksandrazb for finding this method
{
	return ((s << 7) + ~(s >> 3)) + ~m;
}

uint64_t constexpr hashIt(const char* m) // again, credit to @aleksandrazb for finding this method
{
	return (*m) ? mix(*m, hashIt(m + 1)) : 0;
}

int main() {
	core Core; // instantiate a 'Core' object of the 'core' class
	host hJ3ff("J3ff", "127.0.0.1");
	user J3ff("J3ff", 10000);
	char hostname[HOST_NAME_MAX + 1]; // declare a char var 'hostname' with the max_len of 65 bytes;
	gethostname(hostname, HOST_NAME_MAX + 1); // use the gethostname() system call from unistd.h to get the current local machine's hostname
	std::cout << "Terminal Insanity 0.0.03 @ " << hostname << std::flush << std::endl; // print the hostname after the game name + version
	hJ3ff.bInteractiveShell = false; // set the in-game shell interaction bool to false (default)
	Core.init();
	Core.boot();
	Core.lvl1();
	Core.boot();
	Core.lvl2(hJ3ff, J3ff); // here we're passing the instantiated object 'Class' to the function lvl2(), which is expecting a pointer to the 'core' class
	return 0;
}

void core::iterateOverString(std::string &playerMsg, int s, int long ns) {
	struct timespec ts = { s, ns };
	for(long unsigned int i = 0; i < playerMsg.size(); i++)
	{
		std::cout << playerMsg[i] << std::flush; // <3 from @simonSlamka to @aleksandrazb for solving this one :3 this method was her idea
		nanosleep(&ts, NULL);
	}
}

int host::evaluateCmdInput(std::string cmdInputUnprocessed, user& User)
{
	core Core;
	std::string cmdDivision;
	std::string base;
	std::string arg;
	for(auto c : cmdInputUnprocessed)
	{
		if(c == ' ')
		{
			arg = cmdDivision;
			cmdDivision = "";
		}
		else {
			cmdDivision = cmdDivision + c;
		}
	}
	base = cmdDivision;
	if(arg != "")
	{
		swap(base, arg);
	}

	std::string cmdInput = base + arg;
	const char* cmdInputChar = cmdInput.c_str();

	const char* baseChar = base.c_str();
	const char* argChar = arg.c_str();

	////////////////////////////////////////

	switch(hashIt(baseChar))
	{
		case hashIt("whoami"):
			switch(hashIt(argChar))
			{
				case hashIt(""):
					Core.whoami(User);
					break;
				default:
					Core.whoami(User, argChar);
					break;
			}
			break;
		case hashIt("mkdir"):
			switch(hashIt(argChar))
			{
				case hashIt(""):
					std::cerr << "mkdir: missing operand" << "\n";
					break;
				default:
					Core.mkdir(argChar);
					break;
			}
		case hashIt("help"):
			Core.help();
			break;
		case hashIt("who"):
			// code
			break;
		case hashIt("lsgameinfo"):
			Core.lsgameinfo();
			break;
		case hashIt(""):
			break;
		case hashIt("exit"):
			// do nothing
			break;
		default:
			std::cerr << "ongashell: command not found: " << cmdInputChar << std::endl;
			return -1;
			break;
	};
	return 0;
}

void core::makeCoreDirs()
{

}

int core::help()
{
	std::cout << "TermOS help table\n";
	std::cout << "-----------------\n";
	std::cout << "\n";
	std::cout << "help - print this help table\n";
	std::cout << "ls - list directory contents\n";
	std::cout << "cd <directory> - change directory\n";
	std::cout << "cp <source> <target> - copy files\n";
	std::cout << "scp <source> <target> - OpenSSH secure file copy\n";
	std::cout << "rm <file> - remove files\n";
	std::cout << "mkdir <dir> - make directories\n";
	std::cout << "scan - search for nearby WAPs\n";
	std::cout << "ifconfig - display information about a network interface\n";
	std::cout << "iwconfig - display information about a wireless network interface\n";
	std::cout << "whoami - print effective userid\n";
	std::cout << "uptime - tell how long the system has been running\n";
	std::cout << "lshw - list hardware\n";
	std::cout << "nmap <destination IP>/<mask> - network exploration tool and security / port scanner\n";
	std::cout << "aircrack-ng set target <SSID> - set a WAP as a target for cracking\n";
	std::cout << "set_target <local IP> <open port> - set a machine on the local network with an open port as a target\n";
	std::cout << "execute - run a previously configured attack\n";
	//std::cout << "email <email address> - send an email to an email address";
	std::cout << "poweroff - power-off the machine\n";
	std::cout << "lsgameinfo - list info about this game build\n";
	std::cout << "exit - cause normal process termination\n";
	std::cout << "\n";
	return 0;
}

int core::whoami(user& User, const char* arg)
{
	const char* usernameChar = User.username.c_str();
	if(strcmp(usernameChar, "") == 0)
	{
		std::cerr << "FATAL ERROR: username N/A, exiting ..." << std::endl;
		exit(-2);
	}
	const char* m = arg;
	if(strcmp(m, "") == 0)
	{
		std::cout << User.username << std::endl;
		return 0;
	}
	else
	{
		std::cerr << "whoami: extra operand '" << m << "'\n";
		return -1;
	}
}

int core::mkdir(const char* name)
{
	file Dir(name, currentDir, "", true);
	return 0;
}

int core::lsgameinfo()
{
	std::cout << "Terminal Insanity by Ongakken" << "\n";
	std::cout << "Version: 0.0.03" << "\n";
	return 0;
}

void host::spawnShell(host& Host, user& User)
{
	while(Host.bInteractiveShell)
	{
		std::cout << "$ ";
		std::getline(std::cin, cmdInput); // !!! WARN: DO NOT use cin >> var; in here, it WILL NOT work, because std::cin stops reading at whitespace !!!
		Host.evaluateCmdInput(cmdInput, User);
		const char* cmdInputChar = cmdInput.c_str();
		//if(strcmp(cmdInputChar, "") == 0)
		//{
		//	std::cout << "\n";
		//}
		if(strcmp(cmdInputChar, "exit") == 0)
		{
			bInteractiveShell = false;
			break;
		}
	}
}

void core::init() {
	system("wmctrl -r ':ACTIVE:' -b add,fullscreen");
	system("PATH=$PATH:/opt/ongakken/terminalInsanity");
	system("/usr/bin/zsh -c '[ -d /opt/ongakken/terminalInsanity ] && [ -d /opt/ongakken/terminalInsanity/sounds ] && [ -d /opt/ongakken/terminalInsanity/img ] && printf '\a''");
	sleep(1);
	system("grep 'zsh' /etc/shells >> /dev/null && printf '\a'");
	sleep(1);
	system("./zshVerify.sh >> /dev/null && printf '\a'");
	sleep(1);
	system("kitty -o allow_remote_control=yes --title OngakkenLogo --listen-on unix:/tmp/terminalInsanity --hold viu /opt/ongakken/logo.png &");
	system("paplay /opt/ongakken/terminalInsanity/sounds/intro.wav &");
	struct timespec ts = { 0, 2000000000 };
	nanosleep(&ts, NULL);
	system("killall paplay");
	sleep(1);
	system("kitty @ --to unix:/tmp/terminalInsanity close-window --match title:OngakkenLogo");
}

void core::boot() {
	std::cout << "\033]0;" << "Terminal" << "\007";
	system("clear");
	std::cout << "Booting ...\n\n";
	sleep(2);
	system("printf '[\e[32mOK\e[0m] Mounting the root filesystem ...\n'");
	std::cout << "\n";
	sleep(2);
	system("printf '[\e[32mOK\e[0m] Running /sbin/init ...\n'");
	std::cout << "\n";
	sleep(1);
	system("printf '[\e[32mOK\e[0m] Starting runlevel programs ...\n'");
	std::cout << "\n";
	sleep(1);
	std::ifstream f("/opt/ongakken/terminalInsanity/dmesg");
	if (f.is_open()) {
	std::cout << f.rdbuf();
	}
	std::cout << "\n";
	system("printf '[\e[31mFAIL\e[0m] Scanning for friendly network devices ...\n'");
	std::cout << "\n";
	sleep(4);
	system("printf '[\e[32mOK\e[0m] Running post-boot runlevel subroutine 'readme' ...'");
	sleep(1);
	system("clear");
}

void core::lvl1() {
	std::cout << "\033]0;" << "Terminal" << "\007";
	system("paplay /opt/ongakken/terminalInsanity/OST/incoming.wav &");
	system("clear");
	sleep(3);
	std::cout << "Dissonance channel connection established\n\n";
	std::cout << "------------------------------------";
	std::cout << "\n";
	std::cout << "\n\n";
	sleep(3);
	system("printf '\e[34mJason:\e[0m we need to figure something out ...\n'");
	std::cout << "\n";
	sleep(4);
	system("printf '\e[95mMark:\e[0m agreed, we cannot just sit and do nothing\n'");
	std::cout << "\n";
	sleep(6);
	system("printf '\e[34mJason:\e[0m where is J3ff btw?\n'");
	std::cout << "\n";
	sleep(3);
	system("printf '\e[95mMark:\e[0m idk\n'");
	std::cout << "\n";
	sleep(4);
	system("printf '%s' '\e[36mJ3ff:\e[0m'");
	playerMsg = (" Hey guys");
	iterateOverString(playerMsg, 0, 100000000);
	std::cout << "\n\n";
	sleep(6);
	system("printf '\e[95mMark:\e[0m nice of you to finally show up..\n'");
	std::cout << "\n";
	sleep(1);
	system("printf '\e[34mJason:\e[0m hey man\n'");
	sleep(7);
	system("printf '\e[34mJason:\e[0m we were just discussing the plan\n'");
	std::cout << "\n";
	sleep(3);
	system("printf '%s' '\e[36mJ3ff:\e[0m'");
	playerMsg = (" So how are we gonna do it?");
	iterateOverString(playerMsg, 0, 100000000);
	std::cout << "\n\n";
	sleep(9);
	system("printf '\e[95mMark:\e[0m well, for starters, we need more people.\n'");
	sleep(7);
	system("printf '\e[95mMark:\e[0m even though we can do it skill-wise, we do not have time, so we need more firepower\n'");
	sleep(11);
	system("printf '\e[95mMark:\e[0m i have an idea, but it requires putting aurora up to a difficult recursive search task\n'");
	sleep(12);
	system("printf '\e[95mMark:\e[0m so j3ff, do i have your permission to access her and run the code i wrote?\n'");
	std::cout << "\n";
	sleep(4);
	system("printf '%s' '\e[36mJ3ff:\e[0m'");
	playerMsg = (" Alright, try it. We need this to happen.\n");
	iterateOverString(playerMsg, 0, 100000000);
	std::cout << "\n";
	sleep(5);
	system("printf '\e[95mMark:\e[0m roger. on it\n'");
	std::cout << "\n\n";
	sleep(4);
	system("printf '%s' '\e[33mA week later ...\e[0m\n' | pv -qL 3"); // I'm keeping the 'pv' approach here just in case, so we'll know how to use it later
	std::cout << "\n\n";
	sleep(2);
}

void core::lvl2(host& hJ3ff, user& J3ff)
{
	std::cout << "\033]0;" << "Terminal" << "\007";
	system("clear");
	//hJ3ff.bInteractiveShell = true;
	//hJ3ff.spawnShell(hJ3ff, J3ff);
	std::cout << "\n";
	system("printf '%s' '\e[32mDaily log, Oct. 10, 2022 ...\e[0m\n' | pv -qL 6");
	sleep(2);
	playerMsg = (" I haven't been feeling like myself lately. I don't know.\n");
	iterateOverString(playerMsg, 0, 105000000);
	sleep(1);
	playerMsg = (" It might have something to do with the fact that I've been sleeping less ...\n");
	iterateOverString(playerMsg, 0, 110000000);
	sleep(1);
	playerMsg = (" or maybe it's because we're planning this next big thing and it's just too much\n");
	iterateOverString(playerMsg, 0, 130000000);
	sleep(2);
	playerMsg = (" if we really do this, it's going to be a huge risk for all of us\n");
	iterateOverString(playerMsg, 0, 100000000);
	sleep(2);
	playerMsg = (" but I realize that we need to help them. If what they think is coming is correct,\n it's our civic duty to try and prevent it\n");
	iterateOverString(playerMsg, 0, 110000000);
	sleep(1);
	playerMsg = (" I told Mark to run the code he wrote, so we'll see where that leads to. We need to move ...\n");
	iterateOverString(playerMsg, 0, 120000000);
	sleep(2);
	playerMsg = (" alright, I gotta go. I'll append to this log if there's anything important to write down later on. See you\n");
	iterateOverString(playerMsg, 0, 100000000);
	sleep(3);
	std::cout << '\n';
	std::cout << "." << '\n';
	sleep(1);
	std::cout << "." << '\n';
	sleep(1);
	std::cout << "." << '\n';
	sleep(1);

}