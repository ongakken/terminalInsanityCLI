// © Copyright 2021 Ongakken s.r.o. All rights reserved.
//   Terminal Insanity, Ongakken, the alternative names オンガッケン, オンがッけン, the Ongakken logo, the Ongakken symbol, the Ongakken pattern are trademarks of Ongakken s.r.o.
//   Based on a 2016 videogame 'Terminal Insanity' by Simon Slamka

#include "main.h"

//using namespace std; //standard namespace for using cout, cin and some other without defining the namespace they're in (std::cout)

int main()
{
	core Core;
	cout << "Terminal Insanity 0.00.03\n";
	Core.init();
	Core.boot();
	Core.lvl1();
    return 0;
}

void core::iterateOverString()
{

}

int core::init()
{
	//string x;
	system("/usr/bin/zsh -c '[ -d /opt/ongakken/terminalInsanity ] && [ -d /opt/ongakken/terminalInsanity/sounds ] && [ -d /opt/ongakken/terminalInsanity/img ] && printf '\a''");
	sleep(1);
	system("grep 'zsh' /etc/shells >> /dev/null && printf '\a'");
	sleep(1);
	system("./zshVerify >> /dev/null && printf '\a'");
	//cout << "$ ";
	//getline(cin, x, '\n');
	//system("! /bin/sed -r -e 's/\x0.*//' /proc/$$/cmdline | grep 'zsh' >> /dev/null && /usr/bin/zsh");
	//system("/bin/sed -r -e 's/\x0.*//' /proc/$$/cmdline | grep 'zsh'");
	usleep(500000);
	system("kitty -o allow_remote_control=yes --title OngakkenLogo --listen-on unix:/tmp/terminalInsanity --hold viu /opt/ongakken/logo.png &");
	system("paplay /opt/ongakken/terminalInsanity/sounds/intro.wav &");
	usleep(1700000);
	system("killall paplay");
	sleep(1);
	system("kitty @ --to unix:/tmp/terminalInsanity close-window --match title:OngakkenLogo");
	return 0;
}

int core::boot()
{
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
	if (f.is_open())
	{
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

int core::lvl1()
{
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
	system("printf '%s' '\e[36mJ3ff:\e[0m' && printf ' Hey guys\n' | pv -qL 9");
	cout << "\n";
	sleep(6);
	system("printf '\e[95mMark:\e[0m nice of you to finally show up..\n'");
	cout << "\n";
	usleep(150000);
	system("printf '\e[34mJason:\e[0m hey man\n'");
	sleep(7);
	system("printf '\e[34mJason:\e[0m we were just discussing the plan\n'");
	cout << "\n";
	sleep(3);
	system("printf '%s' '\e[36mJ3ff:\e[0m' && printf ' So how are we gonna do it?\n' | pv -qL 9");

	sleep(9);
}