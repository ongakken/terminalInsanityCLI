// © Copyright 2020 - 2021 Ongakken s.r.o. All rights reserved.
// Ongakken, the alternative names オンガッケン, オンがッけン, the Ongakken logo, the Ongakken symbol, the Ongakken pattern are trademarks of Ongakken s.r.o.

#include "main.h"
#include <cstdio>
#include <iostream>

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
	system("[ -d /opt/ongakken/terminalInsanity ] && peep success");
	system("[ -d /opt/ongakken/terminalInsanity/sounds ] && peep success");
	system("[ -d /opt/ongakken/terminalInsanity/img ] && peep success");
	system("'peep successALL'");
	return 0;
}