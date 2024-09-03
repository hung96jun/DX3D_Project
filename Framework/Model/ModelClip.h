#pragma once

#include "ModelData.h"

class ModelClip
{
public:
	ModelClip();
	~ModelClip();

public:
	void SetName(const wstring Name) { this->Name = Name; }
	void SetFrameRate(const float FrameRate) { this->FrameRate = FrameRate; }
	void SetFrameCount(const UINT FrameCount) { this->FrameCount = FrameCount; }

	const wstring GetName() { return Name; }
	const float GetFrameRate() { return FrameRate; }
	const UINT GetFrameCount() { return FrameCount; }

	void SetKeyFrame(wstring Tag, KeyFrame* Frame) { KeyFrames.insert({ Tag, Frame }); }
	KeyFrame* GetKeyFrame(wstring Name);

private:
	wstring Name;

	float FrameRate;
	UINT FrameCount;

	unordered_map<wstring, KeyFrame*> KeyFrames;
};

