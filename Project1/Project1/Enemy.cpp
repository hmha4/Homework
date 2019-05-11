#include "stdafx.h"
#include "Enemy.h"
#include "Render.h"



Enemy::Enemy(const char * face, int position, unsigned int hp, Screen * screen)
	: Character(face, position, hp, screen)
	, blinkTime(0.0f), moveTime(0.0f)
	, attackTime(0.0f), attackDuration(0.0f), attackCoolDown(0.0f)
{
	state = STATE::IDLE;
	next = nullptr;
	prev = nullptr;
}


Enemy::~Enemy()
{
}

void Enemy::Update(int c)
{
	switch (state)
	{
		case Enemy::STATE::IDLE:
		{
			moveTime += 0.016f;
			if (moveTime >= 2.0f)
			{
				int position = GetPosition();
				int nextPos = (position + rand() % 2 - 1) % GetScreenSize();
				if (nextPos - position < 0)
					SetDirection(DIRECTION::ELeft);
				else SetDirection(DIRECTION::ERight);
				position = nextPos;

				SetPosition(position);

				moveTime = 0.0f;
			}
			

			if (GetHP() <= 0)
				state = STATE::BLINK;

			break;
		}
		case Enemy::STATE::BLINK:
		{
			blinkTime += 0.016f;
			SetActive(!GetActive());
			if (blinkTime >= 1.0f)
			{
				blinkTime = 0.0f;
				state = STATE::DIE;
			}

			break;
		}
		case Enemy::STATE::DIE:
		{
			SetActive(false);
			break;
		}
	}

	if (GetPosition() + GetFaceSize() > GetScreenSize())
		SetPosition(GetScreenSize() - (int)GetFaceSize());
	if (GetPosition() < 0)
		SetPosition(0);

	__super::Update();
}

void Enemy::Spawn(int pos, int hp)
{
	state = STATE::IDLE;
	blinkTime = 0.0f;

	SetPosition(pos);
	SetHP(hp);
	SetActive(true);
}

void Enemy::Attack(Character * character)
{
	attackTime += 0.016f;
	attackDuration += 0.016f;

	if (attackDuration < 3.0f)
	{
		if (attackTime >= 1.0f)
		{
			character->SetHP(character->GetHP() - 2);
			attackTime = 0.0f;
		}
	}
	else
	{
		attackCoolDown += 0.016f;

		if (attackCoolDown >= 2.0f)
		{
			attackCoolDown = 0.0f;
			attackDuration = 0.0f;
		}
	}
}
