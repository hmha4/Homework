#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(const char * face, class Screen * screen);
	~Bullet();

	void Fire(class Character * character);
	void Update();
	bool Collision(class Character * character);

public:
	void SetNext(Bullet * bullet) { next = bullet; }
	Bullet * GetNext() { return next; }

	void SetPrev(Bullet * bullet) { prev = bullet; }
	Bullet * GetPrev() { return prev; }
private:
	int speed;

	Bullet * next;
	Bullet * prev;
};

