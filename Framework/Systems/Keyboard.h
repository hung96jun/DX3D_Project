#pragma once
#include <bitset>
#include <functional>

#define MAX_INPUT_KEY 255
#define MAX_INPUT_MOUSE 8

enum class KeyState : int
{
	NONE = 0,
	DOWN,
	UP,
	PRESS,
};

bool operator==(const int& value1, const KeyState& value2)
{
	return value1 == static_cast<int>(value2);
}

bool operator!=(const int& value1, const KeyState& value2)
{
	return value1 != static_cast<int>(value2);
}

class Keyboard
{
private:
	Keyboard();
	~Keyboard();

public:
	static Keyboard* Get();

	static void Create();
	static void Delete();

	void Update();

	const bool IsDown(const DWORD key) { return KeyMap[key] == KeyState::DOWN; }
	const bool IsUp(const DWORD key) { return KeyMap[key] == KeyState::UP; }
	const bool IsPress(const DWORD key) { return KeyMap[key] == KeyState::PRESS; }

	const bool AddDynamic(const DWORD key, const KeyState state, function<void()> func);

private:
	static Keyboard* Instance;

	bitset<MAX_INPUT_KEY> AssignedKeys;
	map<DWORD, vector<function<void()>>> KeyEvents;

	byte KeyCurState[MAX_INPUT_KEY] = {};
	byte KeyBeforeState[MAX_INPUT_KEY] = {};
	byte KeyMap[MAX_INPUT_KEY] = {};
};

