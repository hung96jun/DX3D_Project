#pragma once

#include <iostream>
#include <string>

using namespace std;

namespace Utility
{
	wstring GetFileExtension(const wstring File);
	/**
	* ��� ���� ���� �̸� ����
	*/
	string GetFileName(const string File);
	string GetFileNameWithoutExtension(const string File);
}

using namespace Utility;