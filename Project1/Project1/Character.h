#pragma once
#include "GameObject.h"

class Character : public GameObject
{
public:
	enum class DIRECTION
	{
		ELeft, ERight
	};

public:
	Character(const char * face, int position, unsigned int hp, class Screen * screen);
	virtual ~Character();

	virtual void Update(int c = 0);

public:
	void SetHP(unsigned int val) { 
		hp = val; 
		char buffer[3];
		_itoa(hp, buffer, 10);
		strcpy(life, " HP : ");
		strcat(life, buffer);
	}
	unsigned int GetHP() { return hp; }

	void SetDirection(DIRECTION dir) { this->dir = dir; }
	DIRECTION GetDirection() { return dir; }

private:
	unsigned int hp;
	DIRECTION dir;
};

