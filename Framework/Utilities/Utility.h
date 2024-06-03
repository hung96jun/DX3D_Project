#pragma once

using namespace std;

namespace Utility
{
	const string ToString(wstring Str);
	const wstring ToString(string Str);

	wstring GetFileExtension(const wstring File);
	/**
	* ��� ���� ���� �̸� ����
	*/
	string GetFileName(const string File);
	string GetFileNameWithoutExtension(const string File);

	vector<string>  SplitString(string Origin, const string& Tok, const bool& IncludeLast = true);

	const bool ExistDirectory(const string File);
	void CreateFolders(const string File);

	bool StartWidth(string Str, string Comp);

	void StrChange(string* Str, string Target, string ChangeStr);
	void StrChange(wstring* Str, wstring Target, wstring ChangeStr);
}

using namespace Utility;