#include "Shader.h"

Shader::Shader(const wstring File)
	:File(File)
{
	CONSTRUCTOR_DEBUG();
}

Shader::~Shader()
{
	DESTRUCTOR_DEBUG();
	Blob->Release();
}
