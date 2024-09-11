#include "Framework.h"
#include "BinaryRead.h"
#include "Math/Vector.h"
#include "Math/Transformation.h"

BinaryRead::BinaryRead(string FilePath)
{
	CONSTRUCTOR_DEBUG();

	assert(FilePath.length() > 0);
	//FileHandle = CreateFileA(FilePath.c_str(), GENERIC_READ,
	//	FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	FileHandle = CreateFileA
	(
		FilePath.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ, nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);

	bool isCheck = FileHandle != INVALID_HANDLE_VALUE;
	assert(isCheck);

#if DEBUG == 1
	{
		int index = static_cast<int>(FilePath.find_last_of('.'));
		string debugFilePath = FilePath.substr(0, index);
		debugFilePath += "_Read.txt";
		this->DebugFile.open(debugFilePath, std::ios_base::out);

		if (!DebugFile.is_open())
		{
			MessageBoxA(nullptr, "Failed to open debug file", "Debug Error", MB_OK | MB_ICONERROR);
			exit(EXIT_FAILURE);
		}
	}
#endif
}

BinaryRead::~BinaryRead()
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

bool BinaryRead::ReadBool()
{
	bool result = false;
	ReadFile(FileHandle, &result, sizeof(bool), &Size, nullptr);

#if DEBUG == 1
	if (result == true)
		DebugFile << "bool : " << "True" << endl;
	else
		DebugFile << "bool : " << "False" << endl;
#endif // DEBUG == 1

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

#if DEBUG == 1
	DebugFile << "int : " << to_string(result) << endl;
#endif // DEBUG == 1

	return result;
}

UINT BinaryRead::ReadUInt()
{
	UINT result = 0;
	ReadFile(FileHandle, &result, sizeof(UINT), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "uint : " << to_string(result) << endl;
#endif // DEBUG == 1

	return result;
}

float BinaryRead::ReadFloat()
{
	float result = 0.0f;
	ReadFile(FileHandle, &result, sizeof(float), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "float : " << to_string(result) << endl;
#endif // DEBUG == 1


	return result;
}

double BinaryRead::ReadDouble()
{
	double result = 0.0;
	ReadFile(FileHandle, &result, sizeof(double), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "double : " << to_string(result) << endl;
#endif // DEBUG == 1

	return result;
}

Vector2 BinaryRead::ReadVector2()
{
	Vector2 result = { 0.0f, 0.0f };
	ReadFile(FileHandle, &result, sizeof(Vector2), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "vector2 : " << result.ToString() << endl;
#endif // DEBUG == 1

	return result;
}

Vector3 BinaryRead::ReadVector3()
{
	Vector3 result = { 0.0f, 0.0f, 0.0f };
	ReadFile(FileHandle, &result, sizeof(Vector3), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "vector3 : " << result.ToString() << endl;
#endif // DEBUG == 1

	return result;
}

Vector4 BinaryRead::ReadVector4()
{
	Vector4 result = { 0.0f, 0.0f, 0.0f, 0.0f };
	ReadFile(FileHandle, &result, sizeof(Vector4), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "vector4 : " << result.ToString() << endl;
#endif // DEBUG == 1

	return result;
}

Transformation BinaryRead::ReadTransform()
{
	Transformation result;
	ReadFile(FileHandle, &result, sizeof(Transformation), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "transform" << endl << result.ToString() << endl;
#endif // DEBUG == 1

	return result;
}

Matrix BinaryRead::ReadMatrix()
{
	Matrix result;
	ReadFile(FileHandle, &result, sizeof(Matrix), &Size, nullptr);

#if DEBUG == 1
	DebugFile << "matrix" << endl << Transformation::ToString(result) << endl;
#endif // DEBUG == 1

	return result;
}

string BinaryRead::ReadString()
{
	UINT length = ReadUInt();
	//char* result = new char[length + 1];
	string result(length, '\0');
	ReadFile(FileHandle, &result[0], sizeof(char) * length, &Size, nullptr);

#if DEBUG == 1
	DebugFile << "string : " << result << endl;
#endif

	return result;
}

void BinaryRead::ReadByte(void** result, UINT DataSize)
{
	ReadFile(FileHandle, *result, DataSize, &Size, nullptr);

#if DEBUG == 1
	DebugFile << "ByteData : " << result << ", " << to_string(Size) << " Byte" << endl;
#endif // DEBUG == 1
}