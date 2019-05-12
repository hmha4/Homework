#include "../stdafx.h"
#include "Time.h"

Time * Time::instance = nullptr;

void Time::Create()
{
	assert(instance == nullptr);

	instance = new Time();
}

void Time::Delete()
{
	assert(instance != nullptr);

	delete instance;
}

Time * Time::Get()
{
	return instance;
}

Time::Time()
	: deltaTime(0.01f), fps(1.0f / 60.0f)
	, currentTime(0.0f), elapsedTime(0.0f)
{
	currentTime = (float)clock();
}


Time::~Time()
{
}

void Time::Update()
{
	float newTime = (float)clock();
	float frameTime = newTime - currentTime;
	currentTime = newTime;

	deltaTime = min(frameTime, fps);
	elapsedTime += deltaTime;
}

