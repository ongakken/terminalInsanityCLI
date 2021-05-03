// © Copyright 2020 - 2021 Ongakken s.r.o. All rights reserved.
//   Ongakken, the alternative names オンガッケン, オンがッけン, the Ongakken logo, the Ongakken symbol, the Ongakken pattern are trademarks of Ongakken s.r.o.

#include "main.h"

using namespace std; //standard namespace for using cout, cin and some other without defining the namespace they're in (std::cout)

int main()
{
	core Core;
	cout << "hello from terminalInsanityCONSOLE!\n";
	Core.init();
    return 0;
}

int core::init()
{
	system("[ -d /opt/ongakken/terminalInsanity ] && echo '\a'");
	sleep(1);
	system("[ -d /opt/ongakken/terminalInsanity/sounds ] && echo '\a'");
	sleep(1);
	system("[ -d /opt/ongakken/terminalInsanity/img ] && echo '\a'");
	return 0;
}