#pragma once
class Time
{
public:
	Time();
	~Time();

	void Update();

	float Running() { return elapsedTime; }
	float Delta() { return deltaTime * 6; }


private:
	float elapsedTime;
	float deltaTime;

	float currentTime;
	float fps;
public:
	static void Create();
	static void Delete();
	static Time * Get();
private:
	static Time * instance;
};

