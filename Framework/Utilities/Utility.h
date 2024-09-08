#pragma once
//#include "Renders/VertexLayout.h"
#include "Model/ModelData.h"

using namespace std;

//typedef VertexUVNormalTangentBlend VertexModel;

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

	bool StartWith(string Str, string Comp);

	void StrChange(string* Str, string Target, string ChangeStr);
	void StrChange(wstring* Str, wstring Target, wstring ChangeStr);

	void DivisionMatrix(OUT Float4& Dest, Matrix Source, const int Index);
	Float4 DivisionMatrix(Matrix Source, const int Index);

	void StringReplace(string* Str, string Dest, string Source);
	void StringReplace(wstring* Str, wstring Dest, wstring Source);

	template<typename T>
	string ConvertToString(const T& Data)
	{
		if constexpr (std::is_convertible_v<T, string>)
			return "Value : " + string(Data) + "\n";
		else if constexpr (is_arithmetic_v<T>)
			return "Value : " + to_string(Data) + "\n";
		else
			return "Undefine Type\n";
	}
	template<>
	inline string ConvertToString(const VertexModel& Data)
	{
		string result = "";
		result += "{";
		result += "\nPos : " + to_string(Data.Position.x) + ", " + to_string(Data.Position.y) + ", " + to_string(Data.Position.z);
		result += "\nUV : " + to_string(Data.Uv.x) + ", " + to_string(Data.Uv.y);
		result += "\nNormal : " + to_string(Data.Normal.x) + ", " + to_string(Data.Normal.y) + ", " + to_string(Data.Normal.z);
		result += "\nTangent : " + to_string(Data.Tangent.x) + ", " + to_string(Data.Tangent.y) + ", " + to_string(Data.Tangent.z);
		result += "\nIndices : " + to_string(Data.Indices.x) + ", " + to_string(Data.Indices.y) + ", " + to_string(Data.Indices.z) + ", " + to_string(Data.Indices.w);
		result += "\nWeights : " + to_string(Data.Weights.x) + ", " + to_string(Data.Weights.y) + ", " + to_string(Data.Weights.z) + ", " + to_string(Data.Weights.w);
		result += "\n}\n";
		return result;
	}
}

using namespace Utility;