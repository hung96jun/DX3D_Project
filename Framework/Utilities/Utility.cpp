#include "Utility.h"

wstring Utility::GetFileExtension(const wstring File)
{
    size_t index = File.find_last_of('.');

    return File.substr(index + 1);
}

string Utility::GetFileName(const string File)
{
    size_t index = File.find_last_of('/');

    return File.substr(index + 1);
}

string Utility::GetFileNameWithoutExtension(const string File)
{
    string fileName = GetFileName(File);
    size_t index = fileName.find_last_of('.');
    fileName.erase(index);

    return fileName;
}
  