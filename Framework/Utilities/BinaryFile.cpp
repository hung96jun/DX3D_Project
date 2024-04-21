#include "Framework.h"
#include "BinaryFile.h"
#include "Math/Vector.h"
#include "Math/Transformation.h"

///////////////////////////////////////////////////////////////////////////////
BinaryWrite::BinaryWrite(wstring FilePath)
	:FileHandle(nullptr), Size(0)
{
	assert(FilePath.length() > 0);
	FileHandle = CreateFile
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
}

BinaryWrite::~BinaryWrite()
{
	if (FileHandle != nullptr)
	{
		CloseHandle(FileHandle);
		FileHandle = nullptr;
	}
}

void BinaryWrite::WriteBool(const bool Data)
{
	WriteFile(FileHandle, &Data, sizeof(bool), &Size, nullptr);
}

void BinaryWrite::WriteWord(const WORD Data)
{
	WriteFile(FileHandle, &Data, sizeof(WORD), &Size, nullptr);
}

void BinaryWrite::WriteInt(const int Data)
{
	WriteFile(FileHandle, &Data, sizeof(int), &Size, nullptr);
}

void BinaryWrite::WriteUInt(const UINT Data)
{
	WriteFile(FileHandle, &Data, sizeof(UINT), &Size, nullptr);
}

void BinaryWrite::WriteFloat(const float Data)
{
	WriteFile(FileHandle, &Data, sizeof(float), &Size, nullptr);
}

void BinaryWrite::WriteDouble(const double Data)
{
	WriteFile(FileHandle, &Data, sizeof(double), &Size, nullptr);
}

void BinaryWrite::WriteVector2(const Vector2& Data)
{
	WriteFile(FileHandle, &Data, sizeof(Vector2), &Size, nullptr);
}

void BinaryWrite::WriteVector3(const Vector3& Data)
{
	WriteFile(FileHandle, &Data, sizeof(Vector3), &Size, nullptr);
}

void BinaryWrite::WriteVector4(const Vector4& Data)
{
	WriteFile(FileHandle, &Data, sizeof(Vector4), &Size, nullptr);
}

void BinaryWrite::WriteTransform(const Transformation& Data)
{
	WriteFile(FileHandle, &Data, sizeof(Transformation), &Size, nullptr);
}

void BinaryWrite::WriteMatrix(const Matrix& Data)
{
	WriteFile(FileHandle, &Data, sizeof(Matrix), &Size, nullptr);
}

void BinaryWrite::WriteString(const string& Data)
{
	WriteUInt(Data.size());
	const char* str = Data.c_str();
	WriteFile(FileHandle, str, sizeof(char) * Data.size(), &Size, nullptr);
}

void BinaryWrite::WriteWString(const wstring& Data)
{
	WriteUInt(Data.size());
	const WCHAR* str = Data.c_str();
	WriteFile(FileHandle, str, sizeof(WCHAR) * Data.size(), &Size, nullptr);
}

void BinaryWrite::WriteByte(void* Data, UINT DataSize)
{
	WriteFile(FileHandle, Data, DataSize, &Size, nullptr);
}

//////////////////////////////////////////////////////////////////////////////

BinaryRead::BinaryRead(wstring FilePath)
{
	assert(FilePath.length() > 0);
	FileHandle = CreateFile
	(
		FilePath.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);

	bool isCheck = FileHandle != INVALID_HANDLE_VALUE;
	assert(isCheck);
}

BinaryRead::~BinaryRead()
{
	if (FileHandle != nullptr)
	{
		CloseHandle(FileHandle);
		FileHandle = nullptr;
	}
}

bool BinaryRead::ReadBool()
{
	bool result = false;
	ReadFile(FileHandle, &result, sizeof(bool), &Size, nullptr);
	return result;
}

WORD BinaryRead::ReadWord()
{
	WORD result = 0;
	ReadFile(FileHandle, &result, sizeof(WORD), &Size, nullptr);
	return result;
}

int BinaryRead::ReadInt()
{
	int result = 0;
	ReadFile(FileHandle, &result, sizeof(int), &Size, nullptr);
	return result;
}

UINT BinaryRead::ReadUInt()
{
	UINT result = 0;
	ReadFile(FileHandle, &result, sizeof(UINT), &Size, nullptr);
	return result;
}

float BinaryRead::ReadFloat()
{
	float result = 0.0f;
	ReadFile(FileHandle, &result, sizeof(float), &Size, nullptr);
	return result;
}

double BinaryRead::ReadDouble()
{
	double result = 0.0;
	ReadFile(FileHandle, &result, sizeof(double), &Size, nullptr);
	return result;
}

Vector2 BinaryRead::ReadVector2()
{
	Vector2 result = { 0.0f, 0.0f };
	ReadFile(FileHandle, &result, sizeof(Vector2), &Size, nullptr);
	return result;
}

Vector3 BinaryRead::ReadVector3()
{
	Vector3 result = { 0.0f, 0.0f, 0.0f };
	ReadFile(FileHandle, &result, sizeof(Vector3), &Size, nullptr);
	return result;
}

Vector4 BinaryRead::ReadVector4()
{
	Vector4 result = { 0.0f, 0.0f, 0.0f, 0.0f };
	ReadFile(FileHandle, &result, sizeof(Vector4), &Size, nullptr);
	return result;
}

Transformation BinaryRead::ReadTransform()
{
	Transformation result;
	ReadFile(FileHandle, &result, sizeof(Transformation), &Size, nullptr);
	return result;
}

Matrix BinaryRead::ReadMatrix()
{
	Matrix result;
	ReadFile(FileHandle, &result, sizeof(Matrix), &Size, nullptr);
	return result;
}

string BinaryRead::ReadString()
{
	UINT length = ReadUInt();
	char* result = new char[length + 1];
	ReadFile(FileHandle, result, sizeof(char) * length, &Size, nullptr);
	return result;
}

wstring BinaryRead::ReadWString()
{
	UINT length = ReadUInt();
	WCHAR* result = new WCHAR[length + 1];
	ReadFile(FileHandle, result, sizeof(WCHAR) * length, &Size, nullptr);
	return result;
}

void BinaryRead::ReadByte(void** Data, UINT DataSize)
{
	ReadFile(FileHandle, *Data, DataSize, &Size, nullptr);
}

///////////////////////////////////////////////////////////////////////////////