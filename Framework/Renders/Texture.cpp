#include "Libraries.h"
#include "Texture.h"
#include "Systems/D3D.h"
#include "Utilities/Utility.h"

unordered_map<wstring, Texture*> Texture::Textures;

Texture::Texture(ID3D11ShaderResourceView* SRV, ScratchImage& Image, wstring File)
	: SRV(SRV), Image(move(Image)), File(File)
{
}

Texture::~Texture()
{
	SAFE_RELEASE(SRV);
}

Texture* Texture::Add(wstring File)
{
	if (Textures.count(File) > 0)
		return Textures[File];

	ScratchImage image;
	HRESULT result;

	wstring extension = GetFileExtension(File);

	if (extension.compare(L"tga") == 0)
		result = LoadFromTGAFile(File.c_str(), nullptr, image);
	else if (extension.compare(L"dds") == 0)
		result = LoadFromDDSFile(File.c_str(), DDS_FLAGS_NONE, nullptr, image);
	else
		result = LoadFromWICFile(File.c_str(), WIC_FLAGS_NONE, nullptr, image);

	assert(SUCCEEDED(result));

	ID3D11ShaderResourceView* srv;
	CreateShaderResourceView(D3D::GetDevice(), image.GetImages(), image.GetImageCount(),
		image.GetMetadata(), &srv);

	Textures[File] = new Texture(srv, image, File);

	return Textures[File];
}

Texture* Texture::Add(wstring File, wstring Key)
{
	if (Textures.count(Key) > 0)
		return Textures[Key];

	return Add(File);
}

Texture* Texture::Add(wstring Key, ID3D11ShaderResourceView* SRV)
{
	if (Textures.count(Key) > 0)
		return Textures[Key];

	ScratchImage image;
	Textures[Key] = new Texture(SRV, image, Key);

	return Textures[Key];
}

void Texture::Destroy()
{
	for (pair<wstring, Texture*> t : Textures)
		SAFE_DELETE(t.second);
	Textures.clear();
}

void Texture::PSSet(UINT Slot)
{
	D3D::GetDC()->PSSetShaderResources(Slot, 1, &SRV);
}

Vector2 Texture::GetSize()
{
	Vector2 result = Vector2(
		static_cast<float>(Image.GetMetadata().width),
		static_cast<float>(Image.GetMetadata().height)
	);

	return result;
}

void Texture::ReadPixels(vector<Float4>& Pixels)
{
	uint8_t* colors = Image.GetPixels();
	UINT size = Image.GetPixelsSize();

	Pixels.resize(size / 4);
	float scale = 1.0f / 255.0f;

	for (UINT i = 0; i < Pixels.size(); i++)
	{
		Pixels[i].x = colors[i * 4 + 0] * scale;
		Pixels[i].y = colors[i * 4 + 1] * scale;
		Pixels[i].z = colors[i * 4 + 2] * scale;
		Pixels[i].w = colors[i * 4 + 3] * scale;
	}
}
