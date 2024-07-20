#pragma once

using namespace std;

namespace Utility
{
	const string ToString(wstring Str);
	const wstring ToString(string Str);

	// 파일 확장자 추출
	wstring GetFileExtension(const wstring File);
	string GetFileExtension(const string File);
	// 파일명 추출
	wstring GetFileName(const wstring File);
	string GetFileName(const string File);
	// 파일명과 확장자 추출
	wstring GetFileNameWithoutExtension(const wstring File);
	string GetFileNameWithoutExtension(const string File);
	// 파일명과 확장자를 제외한 경로 추출
	wstring GetDirectory(const wstring File);
	string GetDirectory(const string File);

	vector<string>  SplitString(string Origin, const string& Tok, const bool& IncludeLast = true);

	const bool ExistDirectory(const string File);
	void CreateFolders(const string File);

	bool StartWidth(string Str, string Comp);

	void StrChange(string* Str, string Target, string ChangeStr);
	void StrChange(wstring* Str, wstring Target, wstring ChangeStr);
}

using namespace Utility;