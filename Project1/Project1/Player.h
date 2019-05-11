#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(const char * face, int position, unsigned int hp, Screen * screen);
	~Player();

	// Character을(를) 통해 상속됨
	virtual void Update(int c = 0);

	bool IsFire() { return isFire; }
private:
	bool isFire;
};

