#include "Shader.h"

Shader::Shader(const wstring File)
	:File(File)
{
}

Shader::~Shader()
{
	Blob->Release();
}
