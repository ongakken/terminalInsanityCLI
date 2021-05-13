// © Copyright 2021 Ongakken s.r.o. All rights reserved.
//   Ongakken, the alternative names オンガッケン, オンがッけン, the Ongakken logo, the Ongakken symbol, the Ongakken pattern are trademarks of Ongakken s.r.o.

#pragma once

using namespace std; //standard namespace for using cout, cin and some other without defining the namespace they're in (std::cout)

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstdio>
#include <iostream>
#include <fstream>

class core
{
public:
	int init();
	int boot();
	int lvl1();
	void iterateOverString();
};



