#pragma once
#include "Character.h"
class Enemy : public Character
{
private:
	enum class STATE
	{
		IDLE,
		BLINK,
		DIE
	} state;

public:
	Enemy(const char * face, int position, unsigned int hp, Screen * screen);
	~Enemy();

	virtual void Update(int c = 0);

	bool IsDead() { return state == STATE::DIE; }
	void Spawn(int pos, int hp);
	void Attack(Character * character);
	void SetPlayerPos(int pos);
public:
	void SetNext(Enemy * enemy) { next = enemy; }
	Enemy * GetNext() { return next; }

	void SetPrev(Enemy * enemy) { prev = enemy; }
	Enemy * GetPrev() { return prev; }

private:
	float blinkTime;

	float attackTime;
	float attackDuration;
	float attackCoolDown;

	float moveTime;

	Enemy * next;
	Enemy * prev;

	int playerPos;
};

