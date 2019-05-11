#include "stdafx.h"
#include "Player.h"
#include "Render.h"


Player::Player(const char * face, int position, unsigned int hp, Screen * screen)
	: Character(face, position, hp, screen)
	, isFire(false)
{

}


Player::~Player()
{
}

void Player::Update(int c)
{
	isFire = false;

	switch (c)
	{
	case 'a':
	{
		int position = GetPosition();
		position = (position - 1) % GetScreenSize();
		SetPosition(position);
		SetDirection(DIRECTION::ELeft);
		break;
	}
	case 'd':
	{
		int position = GetPosition();
		position = (position + 1) % GetScreenSize();
		SetPosition(position);
		SetDirection(DIRECTION::ERight);
		break;
	}
	case ' ':
		isFire = true;

		break;
	}

	if (GetPosition() + GetFaceSize() > GetScreenSize())
		SetPosition(GetScreenSize() - (int)GetFaceSize());
	if (GetPosition() < 0)
		SetPosition(0);

	__super::Update();
}
