#include "Framework.h"
#include "Time.h"

Time* Time::Instance = nullptr;
bool Time::bTimeStopped = true;
float Time::ElapsedTime = 0.0f;

Timer* Timer::Instance = nullptr;

///////////////////////////////////////////////////////////////////////////////
// Time class
///////////////////////////////////////////////////////////////////////////////
Time::Time() :
	TickPerSecond(0), CurTime(0), LastTime(0), LastFPSUpdate(0), FPSUpdateIntterval(0),
	FrameCount(0), RunningTime(0), FramePerSecond(0)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&TickPerSecond);
	FPSUpdateIntterval = TickPerSecond >> 1;
}

Time::~Time()
{
}

Time* Time::Get()
{
	assert(Instance != nullptr);
	return Instance;
}

void Time::Create()
{
	assert(Instance == nullptr);
	Instance = new Time();
}

void Time::Delete()
{
	SAFE_DELETE(Instance);
}

void Time::Update()
{
	if (bTimeStopped == true) return;

	QueryPerformanceCounter((LARGE_INTEGER*)&CurTime);
	ElapsedTime = static_cast<float>(CurTime - LastTime) / static_cast<float>(TickPerSecond);
	RunningTime += ElapsedTime;

	FrameCount++;
	if (CurTime - LastFPSUpdate >= FPSUpdateIntterval)
	{
		float tempCurTime = static_cast<float>(CurTime / TickPerSecond);
		float tempLastTime = static_cast<float>(LastFPSUpdate / TickPerSecond);
		FramePerSecond = static_cast<float>(FrameCount / (tempCurTime - tempLastTime));

		LastFPSUpdate = static_cast<INT64>(CurTime);
		FrameCount = 0;
	}

	LastTime = CurTime;
	Timer::Get()->Update();
}

void Time::Print()
{
}

void Time::Start()
{
	if (bTimeStopped == false)
		assert(false);

	QueryPerformanceCounter((LARGE_INTEGER*)&LastTime);
	bTimeStopped = false;
}

void Time::Stop()
{
	if (bTimeStopped == true)
		assert(false);

	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&stopTime);
	RunningTime += static_cast<float>((stopTime - LastTime) / TickPerSecond);
	bTimeStopped = true;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Timer class 
///////////////////////////////////////////////////////////////////////////////
Timer* Timer::Get()
{
	assert(Instance != nullptr);
	return Instance;
}

void Timer::Delete()
{
	SAFE_DELETE(Instance);
}

void Timer::Update()
{
	for (int index : RunningEventKeys)
	{
		TimerEvents[index].Excute();
	}
}

void Timer::ExcuteEvent(const string key)
{
	if (TimerEventKeys.count(key) == 0)
		return;

	RunningEventKeys.push_back(TimerEventKeys[key]);
}

void Timer::AbortEvent(const string key)
{
	if (TimerEventKeys.count(key) == 0)
		return;
	
	TimerEvents[TimerEventKeys[key]].Abort();

	list<int>::iterator it = RunningEventKeys.begin();
	advance(it, TimerEventKeys[key]);
	RunningEventKeys.erase(it);
}

const bool Timer::SetStartEvent(string key, function<void()> func)
{
	if (TimerEventKeys.count(key) == 0)
	{
		pair<string, int> keyPair;
		keyPair.first = key;
		keyPair.second = TimerEventKeys.size();

		TimerEventKeys.insert(keyPair);
		
		TimerEvent event;
		event.SetStartEvent(func);
		TimerEvents.push_back(event);
	}

	else
	{
		int index = TimerEventKeys[key];
		if (TimerEvents[index].IsSetStartEvent() == true)
			return false;

		TimerEvents[index].SetStartEvent(func);
	}

	return true;
}

const bool Timer::SetTicktEvent(string key, const float time, function<void()> func)
{
	if (TimerEventKeys.count(key) == 0)
	{
		pair<string, int> keyPair;
		keyPair.first = key;
		keyPair.second = TimerEventKeys.size();

		TimerEventKeys.insert(keyPair);

		TimerEvent event;
		event.SetTickEvent(func);
		event.SetTimer(time);
		TimerEvents.push_back(event);
	}

	else
	{
		int index = TimerEventKeys[key];
		if (TimerEvents[index].IsSetTickEvent() == true)
			return false;

		TimerEvents[index].SetTickEvent(func);
		TimerEvents[index].SetTimer(time);
	}

	return true;
}

const bool Timer::SetEndtEvent(string key, const float time, function<void()> func)
{
	if (TimerEventKeys.count(key) == 0)
	{
		pair<string, int> keyPair;
		keyPair.first = key;
		keyPair.second = TimerEventKeys.size();

		TimerEventKeys.insert(keyPair);

		TimerEvent event;
		event.SetEndEvent(func);
		event.SetTimer(time);
		TimerEvents.push_back(event);
	}

	else
	{
		int index = TimerEventKeys[key];
		if (TimerEvents[index].IsSetEndEvent() == true)
			return false;

		TimerEvents[index].SetEndEvent(func);
		TimerEvents[index].SetTimer(time);
	}

	return true;
}
///////////////////////////////////////////////////////////////////////////////