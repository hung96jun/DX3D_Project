#include "Libraries.h"
#include "Keyboard.h"
#include "Utilities/Debug.h"

Keyboard* Keyboard::Instance = nullptr;

Keyboard::Keyboard()
{
	CONSTRUCTOR_DEBUG();
}

Keyboard::~Keyboard()
{
	DESTRUCTOR_DEBUG();
}

Keyboard* Keyboard::Get()
{
	if (Instance == nullptr)
		Instance = new Keyboard();

	return Instance;
}

void Keyboard::Destroy()
{
	SAFE_DELETE(Instance);
}

void Keyboard::Update()
{
	memcpy(KeyBeforeState, KeyCurState, sizeof(KeyBeforeState));

	//ZeroMemory(KeyCurState, sizeof(KeyCurState));
	//ZeroMemory(KeyMap, sizeof(KeyMap));

	GetKeyboardState(KeyCurState);

	//for (pair<DWORD, vector<function<void()>>> keys : KeyEvents)
	//{
	//	DWORD index = keys.first;
	//	byte key = KeyCurState[index] & 0x80;
	//	KeyCurState[index] = key ? 1 : 0;

	//	int beforeState = KeyBeforeState[index];
	//	int curState = KeyCurState[index];

	//	if (beforeState == 0 && curState == 1)
	//		KeyMap[index] = KeyState::DOWN;
	//	else if (beforeState == 1 && curState == 0)
	//		KeyMap[index] = KeyState::UP;
	//	else if(beforeState == 1 && curState == 1)
	//		KeyMap[index] = KeyState::PRESS;
	//	else
	//		KeyMap[index] = KeyState::NONE;
	//}

	for (int i = 0; i < MAX_INPUT_KEY; i++)
	{
		byte key = KeyCurState[i] & 0x80;
		KeyCurState[i] = key ? 1 : 0;

		int beforeState = KeyBeforeState[i];
		int curState = KeyCurState[i];

		if (beforeState == 0 && curState == 1)
			KeyMap[i] = KeyState::DOWN;
		else if (beforeState == 1 && curState == 0)
			KeyMap[i] = KeyState::UP;
		else if (beforeState == 1 && curState == 1)
			KeyMap[i] = KeyState::PRESS;
		else
			KeyMap[i] = KeyState::NONE;
	}
}

const bool Keyboard::AddDynamic(const DWORD key, const KeyState state, function<void()> func)
{
	if (KeyEvents.count(key) != 0)
	{
		if (KeyEvents[key][static_cast<int>(state) - 1] == nullptr)
		{
			KeyEvents[key][static_cast<int>(state) - 1] = func;
			return true;
		}
		else
			return false;
	}
	else
	{
		vector<function<void()>> events(3);

		pair<DWORD, vector<function<void()>>> eventPair;
		eventPair.first = key;
		eventPair.second = events;
		eventPair.second[static_cast<int>(state) - 1] = func;

		KeyEvents.insert(eventPair);

		return true;
	}
}
