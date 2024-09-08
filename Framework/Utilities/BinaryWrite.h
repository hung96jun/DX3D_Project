#pragma once

#include "Utilities/Utility.h"

class BinaryWrite
{
public:
	BinaryWrite() = delete;
	BinaryWrite(string FilePath);
	~BinaryWrite();

	void WriteBool(const bool Data);
	void WriteWord(const WORD Data);
	void WriteInt(const int Data);
	void WriteUInt(const UINT Data);
	void WriteFloat(const float Data);
	void WriteDouble(const double Data);

	void WriteVector2(const Vector2& Data);
	void WriteVector3(const Vector3& Data);
	void WriteVector4(const Vector4& Data);
	void WriteTransform(const Transformation& Data);
	void WriteMatrix(const Matrix& Data);

	void WriteString(const string& Data);
	//void WriteWString(const wstring& Data);
	void WriteByte(void* Data, UINT DataSize);
#if DEBUG == 1
	template<typename T>
	void DebugByte(vector<T>& Data)
	{
		for (int i = 0; i < Data.size(); i++)
		{
			DebugFile << "Index : " + to_string(i) << endl;
			DebugFile << ConvertToString<T>(Data[i]) << endl;
		}
	}
#endif

private:
	HANDLE FileHandle;
	DWORD Size;

#if DEBUG == 1
	std::ofstream DebugFile;
#endif
};