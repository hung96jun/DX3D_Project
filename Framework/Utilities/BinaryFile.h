#pragma once

//#include "Utilities/Utility.h"

///////////////////////////////////////////////////////////////////////////////
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
	//template<typename T>
	/*void DebugByte(vector<T>& Data)
	{
		for (int i = 0; i < Data.size(); i++)
		{
			DebugFile << ConvertToString<T>(Data[i]) << endl;
		}
	}*/

private:
	HANDLE FileHandle;
	DWORD Size;

	std::ofstream DebugFile;
};

///////////////////////////////////////////////////////////////////////////////

class BinaryRead
{
public:
	BinaryRead() = delete;
	BinaryRead(wstring FilePath);
	~BinaryRead();

	bool ReadBool();
	WORD ReadWord();
	int ReadInt();
	UINT ReadUInt();
	float ReadFloat();
	double ReadDouble();

	Vector2 ReadVector2();
	Vector3 ReadVector3();
	Vector4 ReadVector4();
	Transformation ReadTransform();
	Matrix ReadMatrix();

	string ReadString();
	//wstring ReadWString();
	void ReadByte(void** Data, UINT DataSize);

private:
	HANDLE FileHandle;
	DWORD Size;
};
///////////////////////////////////////////////////////////////////////////////