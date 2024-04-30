#pragma once

#include <iostream>
#include <string>

using namespace std;

namespace Utility
{
	const string ToString(wstring Str);
	const wstring ToString(string Str);

	wstring GetFileExtension(const wstring File);
	/**
	* 경로 상의 파일 이름 추출
	*/
	string GetFileName(const string File);
	string GetFileNameWithoutExtension(const string File);
}

using namespace Utility;