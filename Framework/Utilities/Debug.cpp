#include <assert.h>
#include "Debug.h"

MemoryDebug* MemoryDebug::Instance = nullptr;

MemoryDebug::MemoryDebug()
{
	path = "../Debug/MemoryLeak_Debug.txt";
	
	DebugFile.open(path);
}

MemoryDebug::~MemoryDebug()
{
	for (pair<string, int> count : Counting)
	{
		if (count.second > 0)
			DebugFile << count.first + " - " + to_string(count.second) << endl;
	}

	if (DebugFile.is_open() == true)
	{
		int a = 10;
		a += 1;
	}

	DebugFile << "Fin" << endl;

	DebugFile.close();
}

MemoryDebug* MemoryDebug::Get()
{
	if (Instance == nullptr)
		Instance = new MemoryDebug();

	return Instance;
}

void MemoryDebug::Destory()
{
	delete Instance;
}

void MemoryDebug::Add(string ClassName)
{
	if (Counting.count(ClassName) == 0)
		Counting.insert({ ClassName, 1 });

	else
		Counting[ClassName]++;
}

void MemoryDebug::Delete(string ClassName)
{
	ClassName = ClassName.substr(1, ClassName.size());

	if (Counting.count(ClassName) == 0)
		DebugFile << ClassName << " - Counting Error" << endl;

	int count = --Counting[ClassName];
	if (count == 0)
	{
		Counting.erase(ClassName);
		DebugFile << ClassName << " Reference 0" << endl;
	}
}
