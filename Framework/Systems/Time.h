#pragma once

class Time
{
private:
	Time();
	~Time();

public:
	static Time* Get();
	static void Destroy();

	const bool IsStopped() { return bTimeStopped; }
	const float GetDeltaTime() { return bTimeStopped ? 0.0f : ElapsedTime; }
	const float GetFPS() { return 1 / GetDeltaTime(); }

	void Update();
	void Print();

	void Start();
	void Stop();

	const float GetFPS() const { return FramePerSecond; }
	const float GetRunning() const { return RunningTime; }

private:
	static Time* Instance;

	static bool bTimeStopped;
	static float ElapsedTime;

	INT64 TickPerSecond;
	INT64 CurTime;
	INT64 LastTime;
	INT64 LastFPSUpdate;
	INT64 FPSUpdateIntterval;

	UINT FrameCount;
	float RunningTime;
	float FramePerSecond;
};

struct TimerEvent
{
public:
	enum class EventState
	{
		NONE = 0,
		START,
		TICK,
		END,
	};

public:
	void SetStartEvent(function<void()> func) { StartEvent = func; }
	void SetTickEvent(function<void()> func) { TickEvent = func; }
	void SetEndEvent(function<void()> func) { EndEvent = func; }
	
	const bool IsSetStartEvent() const { return StartEvent != nullptr; }
	const bool IsSetTickEvent() const { return TickEvent != nullptr; }
	const bool IsSetEndEvent() const { return EndEvent != nullptr; }

	void SetTimer(const float time) { Time = time; }

	const EventState& GetState() const { return State; }

	const bool IsSet() const { return StartEvent != nullptr || TickEvent != nullptr || EndEvent != nullptr; }
	const bool IsRunning() const { return State != EventState::NONE; }
	
	void Abort()
	{
		if (EndEvent != nullptr)
			EndEvent();

		ElapsedTime = 0.0f;
		State = EventState::NONE;
	}

	void Excute()
	{
		switch (State)
		{
		case TimerEvent::EventState::NONE:
		{
			State = EventState::START;
		}
			break;
		case TimerEvent::EventState::START:
		{
			if (StartEvent != nullptr)
				StartEvent();

			State = EventState::TICK;
		}
			break;
		case TimerEvent::EventState::TICK:
		{
			if (TickEvent != nullptr)
				TickEvent();

			if (ElapsedTime >= Time)
				State = EventState::END;
		}
			break;
		case TimerEvent::EventState::END:
		{
			if (EndEvent != nullptr)
				EndEvent();

			State = EventState::NONE;
			ElapsedTime = 0.0f;
		}
			break;
		default:
			break;
		}

		ElapsedTime += Time::Get()->GetDeltaTime();
	}

private:
	function<void()> StartEvent = nullptr;
	function<void()> TickEvent = nullptr;
	function<void()> EndEvent = nullptr;

	EventState State = EventState::NONE;

	float ElapsedTime = 0.0f;
	float Time = 0.0f;
};

class Timer
{
private:
	Timer();
	~Timer();

public:
	static Timer* Get();

	static void Destroy();
	static void Update();
	
	void ExcuteEvent(const string key);
	void AbortEvent(const string key);

	const bool SetStartEvent(const string key, function<void()> func);
	const bool SetTicktEvent(const string key, const float time, function<void()> func);
	const bool SetEndtEvent(const string key, const float time, function<void()> func);

private:
	static Timer* Instance;

	static vector<TimerEvent> TimerEvents;
	static list<int> RunningEventKeys;

	map<string, int> TimerEventKeys;
};