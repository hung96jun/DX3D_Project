#include "Shader.h"

Shader::~Shader()
{
	Blob->Release();
}
