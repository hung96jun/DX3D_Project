#include "Framework.h"
#include "BinaryWrite.h"
#include "Math/Vector.h"
#include "Math/Transformation.h"

BinaryWrite::BinaryWrite(string FilePath)
	:FileHandle(nullptr), Size(0)
{
	CONSTRUCTOR_DEBUG();

	assert(FilePath.length() > 0);
	FileHandle = CreateFileA
	(
		FilePath.c_str(),
		GENERIC_WRITE,
		0, nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);

	bool isCheck = FileHandle != INVALID_HANDLE_VALUE;
	assert(isCheck);

#if DEBUG == 1
	{
		int index = static_cast<int>(FilePath.find_last_of('.'));
		string debugFilePath = FilePath.substr(0, index);
		debugFilePath += "_Write.txt";
		this->DebugFile.open(debugFilePath, std::ios_base::out);
	}
#endif // DEBUG == 1
}

BinaryWrite::~BinaryWrite()
{
	DESTRUCTOR_DEBUG();

	if (FileHandle != nullptr)
	{
		CloseHandle(FileHandle);
		FileHandle = nullptr;
	}

#if DEBUG == 1
	DebugFile.close();
#endif
}

void BinaryWrite::WriteBool(const bool Data)
{
	WriteFile(FileHandle, &Data, sizeof(bool), &Size, nullptr);

#if DEBUG == 1
	if (Data == true)
		DebugFile << "bool : " << "True" << endl;
	else
		DebugFile << "bool : " << "False" << endl;
#endif // DEBUG == 1
}

void BinaryWrite::WriteWord(const WORD Data)
{
	WriteFile(FileHandle, &Data, sizeof(WORD), &Size, nullptr);
}

void BinaryWrite::WriteInt(const int Data)
{
	WriteFile(FileHandle, &Data, sizeof(int), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "int : " << to_string(Data) << endl;
#endif // DEBUG == 1

}

void BinaryWrite::WriteUInt(const UINT Data)
{
	WriteFile(FileHandle, &Data, sizeof(UINT), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "uint : " << to_string(Data) << endl;
#endif // DEBUG == 1
}

void BinaryWrite::WriteFloat(const float Data)
{
	WriteFile(FileHandle, &Data, sizeof(float), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "float : " << to_string(Data) << endl;
#endif // DEBUG == 1
}

void BinaryWrite::WriteDouble(const double Data)
{
	WriteFile(FileHandle, &Data, sizeof(double), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "double : " << to_string(Data) << endl;
#endif // DEBUG == 1
}

void BinaryWrite::WriteVector2(const Vector2& Data)
{
	WriteFile(FileHandle, &Data, sizeof(Vector2), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "vector2 : " << Data.ToString() << endl;
#endif // DEBUG == 1
}

void BinaryWrite::WriteVector3(const Vector3& Data)
{
	WriteFile(FileHandle, &Data, sizeof(Vector3), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "vector3 : " << Data.ToString() << endl;
#endif // DEBUG == 1
}

void BinaryWrite::WriteVector4(const Vector4& Data)
{
	WriteFile(FileHandle, &Data, sizeof(Vector4), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "vector4 : " << Data.ToString() << endl;
#endif // DEBUG == 1
}

void BinaryWrite::WriteTransform(const Transformation& Data)
{
	WriteFile(FileHandle, &Data, sizeof(Transformation), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "transform" << endl << Data.ToString() << endl;
#endif // DEBUG == 1
}

void BinaryWrite::WriteMatrix(const Matrix& Data)
{
	WriteFile(FileHandle, &Data, sizeof(Matrix), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "matrix" << endl << Transformation::ToString(Data) << endl;
#endif // DEBUG == 1
}

void BinaryWrite::WriteString(const string& Data)
{
	WriteUInt(static_cast<UINT>(Data.size()));
	const char* str = Data.c_str();
	WriteFile(FileHandle, str, static_cast<DWORD>(sizeof(char) * Data.size()), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "string : " << Data << endl;
#endif
}

void BinaryWrite::WriteByte(void* Data, UINT DataSize)
{
	WriteFile(FileHandle, Data, DataSize, &Size, nullptr);

#if DEBUG == 1
	DebugFile << "ByteData : " << Data << ", " << to_string(Size) << " Byte" << endl;
#endif // DEBUG == 1
}