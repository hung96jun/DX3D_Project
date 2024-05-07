#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <windows.h>
#include <string>
#include "Defines.h"

#define CONSTRUCTOR_DEBUG()\
{\
if(DEBUG == 1)\
MemoryDebug::Get()->Add(__func__);\
}

#define DESTRUCTOR_DEBUG()\
{\
if(DEBUG == 1)\
MemoryDebug::Get()->Delete(__func__);\
}

using namespace std;

class MemoryDebug
{
private:
	MemoryDebug();
	~MemoryDebug();

public:
	static MemoryDebug* Get();
	static void Destory();

	void Add(string ClassName);
	void Delete(string ClassName);

private:
	static MemoryDebug* Instance;
	map<string, int> Counting;

	string path = "";
	std::ofstream DebugFile;
};

