#include "ModelClip.h"
#include "Utilities/Debug.h"

ModelClip::ModelClip()
{
	CONSTRUCTOR_DEBUG();
}

ModelClip::~ModelClip()
{
	DESTRUCTOR_DEBUG();
}

KeyFrame* ModelClip::GetKeyFrame(wstring Name)
{
	if (KeyFrames.count(Name) < 1)
		return nullptr;

	return KeyFrames[Name];
}
