#include "Framework.h"
#include "Utility.h"

const string Utility::ToString(wstring Str)
{
    string result = "";
    if (Str.size() > 0)
        result.assign(Str.begin(), Str.end());
    return result;
}

const wstring Utility::ToString(string Str)
{
    wstring result = L"";
    if (Str.size() > 0)
        result.assign(Str.begin(), Str.end());
    return result;
}

wstring Utility::GetFileExtension(const wstring File)
{
    size_t index = File.find_last_of(L'.');

    return File.substr(index + 1);
}

string Utility::GetFileExtension(const string File)
{
    size_t index = File.find_last_of(L'.');

    return File.substr(index + 1);
}

wstring Utility::GetFileName(const wstring File)
{
    size_t index = File.find_last_of('/');

    return File.substr(index + 1);
}

string Utility::GetFileName(const string File)
{
    size_t index = File.find_last_of('/');

    return File.substr(index + 1);
}

wstring Utility::GetFileNameWithoutExtension(const wstring File)
{
    wstring fileName = GetFileName(File);
    size_t index = fileName.find_last_of('.');
    fileName.erase(index);

    return fileName;
}

string Utility::GetFileNameWithoutExtension(const string File)
{
    string fileName = GetFileName(File);
    size_t index = fileName.find_last_of('.');
    fileName.erase(index);

    return fileName;
}

wstring Utility::GetDirectory(const wstring File)
{
    wstring file = File;
    if (file.find(L"\\") != string::npos)
        file.replace(file.begin(), file.end(), L"\\", L"/");
    //file += L"/";

    size_t index = file.find_last_of(L"/");
    file = file.substr(0, index + 1);

    return file;
}

string Utility::GetDirectory(const string File)
{
    string file = File;
    if (file.find("\\") != string::npos)
        file.replace(file.begin(), file.end(), "\\", "/");
    //file += L"/";

    size_t index = file.find_last_of("/");
    file = file.substr(0, index + 1);

    return file;
}

vector<string> Utility::SplitString(string Origin, const string& Tok, const bool& IncludeLast)
{
    vector<string> result;

    size_t curAt = 0;

    while ((curAt = Origin.find_first_of(Tok)) != Origin.npos)
    {
        if (curAt > 0)
            result.push_back(Origin.substr(0, curAt));

        Origin = Origin.substr(curAt + 1);
    }

    if (IncludeLast == true && Origin.size() > 0)
        result.push_back(Origin);

    return result;
}

const bool Utility::ExistDirectory(const string File)
{
    DWORD fileValue = GetFileAttributesA(File.c_str());
    bool check = (fileValue != INVALID_FILE_ATTRIBUTES &&
        fileValue & FILE_ATTRIBUTE_DIRECTORY);

    return check;
}

void Utility::CreateFolders(const string File)
{
    vector<string> folders = SplitString(File, "/", false);
    string temp = "";

    for (string folder : folders)
    {
        temp += folder + "/";

        if (ExistDirectory(temp) == false)
            CreateDirectoryA(temp.c_str(), 0);
    }
}

bool Utility::StartWith(string Str, string Comp)
{
    wstring::size_type index = Str.find(Comp);
    if (index != wstring::npos && static_cast<int>(index) == 0)
        return true;
    return false;
}

void Utility::StrChange(string* Str, string Target, string ChangeStr)
{
    //int a = static_cast<int>(std::count(Str->begin(), Str->end(), Target));
    //for (int i = 0; i < a; i++)
    //{
    //    size_t index = Str->find(Target);
    //    if (index == -1)
    //        break;

    //    Str->erase(Str->begin() + index, Str->begin() + index + Target.size());
    //    Str->insert(index, ChangeStr);
    //}

    int index = -1;
    while ((index = static_cast<int>(Str->find(Target))) != -1)
    {
        Str->erase(Str->begin() + index, Str->begin() + index + Target.size());
        Str->insert(index, ChangeStr);
    }
}

void Utility::StrChange(wstring* Str, wstring Target, wstring ChangeStr)
{
    //int a = static_cast<int>(std::count(Str->begin(), Str->end(), Target));
    //for (int i = 0; i < a; i++)
    //{
    //    size_t index = Str->find(Target);
    //    if (index == -1)
    //        break;

    //    Str->erase(Str->begin() + index, Str->begin() + index + Target.size());
    //    Str->insert(index, ChangeStr);
    //}
}

void Utility::DivisionMatrix(OUT Float4& Dest, Matrix Source, const int Index)
{
    XMVECTOR vec = Source.r[Index];
    Dest = Float4(XMVectorGetX(vec), XMVectorGetY(vec), XMVectorGetZ(vec), XMVectorGetW(vec));
}

Float4 Utility::DivisionMatrix(Matrix Source, const int Index)
{
    XMVECTOR vec = Source.r[Index];
    return Float4(XMVectorGetX(vec), XMVectorGetY(vec), XMVectorGetZ(vec), XMVectorGetW(vec));
}

void Utility::StringReplace(string* Str, string Dest, string Source)
{
    string temp = *Str;
    size_t startPos = 0;
    while ((startPos = temp.find(Dest, startPos)) != wstring::npos)
    {
        temp.replace(startPos, Dest.length(), Source);
        startPos += Source.length();
    }

    *Str = temp;
}

void Utility::StringReplace(wstring* Str, wstring Dest, wstring Source)
{
    wstring temp = *Str;
    size_t startPos = 0;
    while ((startPos = temp.find(Dest, startPos)) != wstring::npos)
    {
        temp.replace(startPos, Dest.length(), Source);
        startPos += Source.length();
    }

    *Str = temp;
}
