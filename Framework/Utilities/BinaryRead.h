#pragma once

#include "Utilities/Utility.h"

class BinaryRead
{
public:
	BinaryRead() = delete;
	BinaryRead(string FilePath);
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
#if DEBUG == 1
	template<typename T>
	void DebugByte(vector<T>& Data)
	{
		//for (int i = 0; i < Data.size(); i++)
		//{
		//	DebugFile << "Index : " + to_string(i) << endl;
		//	DebugFile << ConvertToString<T>(Data[i]) << endl;
		//}
	}
#endif

private:
	HANDLE FileHandle;
	DWORD Size;

#if DEBUG == 1
	std::ofstream DebugFile;
#endif
};