#pragma once
#include "GameObject.h"

class Laser : public GameObject
{
public:
	Laser(const char * face, class Screen * screen);
	~Laser();

	void Fire(class Character * start, class Character * target, float duration, float coolTime);
	void Update();

private:
	void Clear();
	void CreateBuffer();

private:
	class Character * start;
	class Character * target;

	int length;
	char * buffer;

	float duration;
	float maxDur;
	float coolTime;
	float maxCool;
	float attackTime;
	bool laserOn;
};

