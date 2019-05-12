#include "stdafx.h"
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
	: deltaTime(0.01)
	, currentTime(0.0), elapsedTime(0.0)
{
	currentTime = clock();
}


Time::~Time()
{
}

void Time::Update()
{
	float newTime = clock();
	float frameTime = newTime - currentTime;
	currentTime = newTime;

	deltaTime = min(frameTime, deltaTime);
	elapsedTime += deltaTime;
}

