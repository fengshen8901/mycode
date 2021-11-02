#pragma once
class CeilingFan
{
public:
	enum SpeedType
	{
		Off,
		Low,
		High
	};

	void SetSpeed(SpeedType t);
	SpeedType GetSpeed();
	void Run();
	void Stop();

private:
	SpeedType speed;
};

