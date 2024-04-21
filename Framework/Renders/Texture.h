#pragma once
#include "Math/Vector.h"

class Texture
{
private:
	Texture() = delete;
	Texture(ID3D11ShaderResourceView* SRV, ScratchImage& Image, wstring File);
	~Texture();

public:
	static Texture* Add(wstring File);
	static Texture* Add(wstring File, wstring Key);
	static Texture* Add(wstring Key, ID3D11ShaderResourceView* SRV);

	static void Destroy();

public:
	void PSSet(UINT Slot = 0);
	Vector2 GetSize();

	void ReadPixels(vector<Float4>& Pixels);

	wstring GetFile() { return File; }
	ID3D11ShaderResourceView* GetSRV() { return SRV; }

private:
	wstring File;
	ScratchImage Image;
	ID3D11ShaderResourceView* SRV;

	static unordered_map<wstring, Texture*> Textures;
};

