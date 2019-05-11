#include "stdafx.h"
#include "Bullet.h"
#include "Character.h"



Bullet::Bullet(const char * face, Screen * screen)
	: GameObject(-1, face, screen)
	, speed(0)
{
	SetActive(false);
	next = nullptr;
	prev = nullptr;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (GetPosition() < 0) return;
	if (GetActive() == false) return;

	if (GetPosition() < 0)
	{
		speed = 0;
		SetPosition(-1);
		SetActive(false);
	}
	if (GetPosition() >= GetScreenSize() - 1)
	{
		speed = 0;
		SetPosition(-1);
		SetActive(false);
	}

	SetPosition(GetPosition() + speed);
}

bool Bullet::Collision(Character * character)
{
	if (GetPosition() < 0) return false;
	if (GetActive() == false) return false;
	if (character->GetHP() <= 0) return false;

	int distance = GetPosition() - character->GetPosition();
	if (distance < 0)
		distance *= -1;

	if (distance <= 1)
	{
		speed = 0;
		SetPosition(-1);
		SetActive(false);
		character->SetHP(character->GetHP() - 1);

		return true;
	}

	return false;
}

void Bullet::Fire(class Character * character)
{
	SetActive(true);

	if (character->GetDirection() == Character::DIRECTION::ELeft)
	{
		speed = -1;
		SetPosition(character->GetPosition());
	}
	else
	{
		speed = 1;
		SetPosition(character->GetPosition() + character->GetFaceSize() - 1);
	}
}
