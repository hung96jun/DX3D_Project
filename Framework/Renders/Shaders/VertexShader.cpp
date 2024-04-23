#include "VertexShader.h"

VertexShader::VertexShader(wstring File)
	:Shader(File)
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	D3DCompileFromFile(File.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS", "vs_5_0", flags, 0, &Blob, nullptr);

	D3D::GetDevice()->CreateVertexShader(Blob->GetBufferPointer(),
		Blob->GetBufferSize(), nullptr, &VShader);

	CreateInputLayout();

	//D3D11_INPUT_ELEMENT_DESC desc[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	//	D3D11_INPUT_PER_VERTEX_DATA, 0},
	//	{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
	//	D3D11_INPUT_PER_VERTEX_DATA, 0},
	//};

	//UINT size = ARRAYSIZE(desc);
	//D3D::GetDevice()->CreateInputLayout(desc, size, 
	//	Blob->GetBufferPointer(), Blob->GetBufferSize(), 
	//	&InputLayout);
}

VertexShader::~VertexShader()
{
	SAFE_RELEASE(VShader);
	SAFE_RELEASE(InputLayout);
}

void VertexShader::Set()
{
	D3D::GetDC()->IASetInputLayout(InputLayout);
	D3D::GetDC()->VSSetShader(VShader, nullptr, 0);
}

void VertexShader::CreateInputLayout()
{
	D3DReflect(Blob->GetBufferPointer(), Blob->GetBufferSize(),
		IID_ID3D11ShaderReflection, (void**)&Reflection);

	D3D11_SHADER_DESC desc;
	Reflection->GetDesc(&desc);

	vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;
	inputLayouts.reserve(desc.InputParameters);

	for (UINT i = 0; i < desc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		Reflection->GetInputParameterDesc(i, &paramDesc);

		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		if (paramDesc.Mask < 2)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask < 4)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask < 8)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask < 16)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		string semanticName = paramDesc.SemanticName;

		if (semanticName == "POSITION")
			elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

		if (semanticName == "TEXCOORD")
			elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;

		int n = static_cast<int>(semanticName.find_first_of('_'));
		semanticName = semanticName.substr(0, n);

		if (semanticName == "INSTANCE")
		{
			elementDesc.InputSlot = 1;
			elementDesc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
			elementDesc.InstanceDataStepRate = 1;
		}

		inputLayouts.push_back(elementDesc);
	}

	D3D::GetDevice()->CreateInputLayout(inputLayouts.data(), static_cast<UINT>(inputLayouts.size()),
		Blob->GetBufferPointer(), Blob->GetBufferSize(), &InputLayout);
}
