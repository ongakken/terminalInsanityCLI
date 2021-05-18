// © Copyright 2021 Ongakken s.r.o. All rights reserved.
//   Terminal Insanity, Ongakken, the alternative names オンガッケン,  オンがッけン, the Ongakken logo, the Ongakken symbol, the Ongakken pattern are trademarks of Ongakken s.r.o.
// Based on a 2016 videogame 'Terminal Insanity' by Simon Slamka

#include "main.h"

// using namespace std; //standard namespace for using cout, cin and some other without defining the namespace they're in (std::cout)

uint64_t constexpr mix(char m, uint64_t s)
{
	return ((s << 7) + ~(s >> 3)) + ~m;
}

uint64_t constexpr hashIt(const char* m)
{
	return (*m) ? mix(*m, hashIt(m + 1)) : 0; // @todo Figure out a way how to prevent recursion here (as reported by the MISRA 17.2 rule)
	// @todo as per the MISRA 18.4 rule, unions are disallowed for any purpose, thus this method needs to be rewritten
}

int main() {
	core Core;
	cout << "Terminal Insanity 0.00.1\n";
	Core.bInteractiveShell = false;
	Core.init();
	Core.boot();
	Core.lvl1();
	Core.boot();
	Core.lvl2(Core);
	return 0;
}

void core::iterateOverString(string &playerMsg, int s, int long ns) {
	struct timespec ts = { s, ns };
	for(long unsigned int i = 0; i < playerMsg.size(); i++)
	{
		cout << playerMsg[i] << flush;
		nanosleep(&ts, NULL);
	}
}

void core::evaluateCmdInput(const char* cmdInputChar)
{
	switch(hashIt(cmdInputChar))
	{
		case hashIt("whoami"):
			whoami();
			break;
		default:
			cout << "ongashell: command not found: " << cmdInputChar << endl;
			break;
	};
}

int core::whoami()
{
	cout << "root\n";
	return 0;
}

void core::spawnShell(core& Core)
{
	while(Core.bInteractiveShell)
	{
		cout << "$ ";
		cin >> Core.cmdInput;
		const char* cmdInputChar = Core.cmdInput.c_str();
		Core.evaluateCmdInput(cmdInputChar);
	}
}

void core::init() {
	// string x;
	system("/usr/bin/zsh -c '[ -d /opt/ongakken/terminalInsanity ] && [ -d /opt/ongakken/terminalInsanity/sounds ] && [ -d /opt/ongakken/terminalInsanity/img ] && printf '\a''");
	sleep(1);
	system("grep 'zsh' /etc/shells >> /dev/null && printf '\a'");
	sleep(1);
	system("./zshVerify >> /dev/null && printf '\a'");
	// cout << "$ ";
	// getline(cin, x, '\n');
	// system("! /bin/sed -r -e 's/\x0.*//' /proc/$$/cmdline | grep 'zsh' >>
	// /dev/null && /usr/bin/zsh"); system("/bin/sed -r -e 's/\x0.*//'
	// /proc/$$/cmdline | grep 'zsh'");
	sleep(1);
	system("kitty -o allow_remote_control=yes --title OngakkenLogo --listen-on unix:/tmp/terminalInsanity --hold viu /opt/ongakken/logo.png &");
	system("paplay /opt/ongakken/terminalInsanity/sounds/intro.wav &");
	struct timespec ts = { 0, 1700000000 };
	nanosleep(&ts, NULL);
	system("killall paplay");
	sleep(1);
	system("kitty @ --to unix:/tmp/terminalInsanity close-window --match title:OngakkenLogo");
}

void core::boot() {
	cout << "\033]0;" << "Terminal" << "\007";
	system("clear");
	cout << "Booting ...\n\n";
	sleep(2);
	system("printf '[\e[32mOK\e[0m] Mounting the root filesystem ...\n'");
	cout << "\n";
	sleep(2);
	system("printf '[\e[32mOK\e[0m] Running /sbin/init ...\n'");
	cout << "\n";
	sleep(1);
	system("printf '[\e[32mOK\e[0m] Starting runlevel programs ...\n'");
	cout << "\n";
	sleep(1);
	ifstream f("/opt/ongakken/terminalInsanity/dmesg");
	if (f.is_open()) {
	cout << f.rdbuf();
	}
	cout << "\n";
	system("printf '[\e[31mFAIL\e[0m] Scanning for friendly network devices ...\n'");
	cout << "\n";
	sleep(4);
	system("printf '[\e[32mOK\e[0m] Running post-boot runlevel subroutine 'readme' ...'");
	sleep(1);
	system("clear");
}

void core::lvl1() {
	cout << "\033]0;" << "Terminal" << "\007";
	system("clear");
	sleep(3);
	cout << "IRC channel connection established\n\n";
	cout << "------------------------------------";
	cout << "\n";
	cout << "\n\n";
	sleep(3);
	system("printf '\e[34mJason:\e[0m we need to figure something out ...\n'");
	cout << "\n";
	sleep(4);
	system("printf '\e[95mMark:\e[0m agreed, we cannot just sit and do nothin\n'");
	cout << "\n";
	sleep(6);
	system("printf '\e[34mJason:\e[0m where is J3ff btw?\n'");
	cout << "\n";
	sleep(3);
	system("printf '\e[95mMark:\e[0m idk\n'");
	cout << "\n";
	sleep(4);
	system("printf '%s' '\e[36mJ3ff:\e[0m'");
	playerMsg = (" Hey guys");
	iterateOverString(playerMsg, 0, 100000000);
	cout << "\n\n";
	sleep(6);
	system("printf '\e[95mMark:\e[0m nice of you to finally show up..\n'");
	cout << "\n";
	sleep(1);
	system("printf '\e[34mJason:\e[0m hey man\n'");
	sleep(7);
	system("printf '\e[34mJason:\e[0m we were just discussing the plan\n'");
	cout << "\n";
	sleep(3);
	system("printf '%s' '\e[36mJ3ff:\e[0m'");
	playerMsg = (" So how are we gonna do it?");
	iterateOverString(playerMsg, 0, 100000000);
	cout << "\n\n";
	sleep(9);
	system("printf '\e[95mMark:\e[0m well, for starters, we need more people.\n'");
	sleep(7);
	system("printf '\e[95mMark:\e[0m even though we can do it skill-wise, we do not have time, so we need more firepower\n'");
	sleep(11);
	system("printf '\e[95mMark:\e[0m i have an idea, but it requires putting aurora up to a difficult recursive search task\n'");
	sleep(12);
	system("printf '\e[95mMark:\e[0m so j3ff, do i have your permission to access her and run the code i wrote?\n'");
	cout << "\n";
	sleep(4);
	system("printf '%s' '\e[36mJ3ff:\e[0m'");
	playerMsg = (" Alright, try it. We need this to happen.");
	iterateOverString(playerMsg, 0, 100000000);
	cout << "\n\n";
	sleep(5);
	system("printf '\e[95mMark:\e[0m roger. on it\n'");
	cout << "\n\n";
	sleep(4);
	system("printf '%s' '\e[33mA week later ...\e[0m\n' | pv -qL 3");
	cout << "\n\n";
	sleep(2);
}

void core::lvl2(core& Core)
{
	cout << "\033]0;" << "Terminal" << "\007";
	system("clear");
	Core.bInteractiveShell = true;
	Core.spawnShell(Core);
}