#include "stdafx.h"
#include "Character.h"

Character::Character(const char * face, int position, unsigned int hp, Screen * screen)
	: GameObject(position, face, screen)
	, hp(hp)
{
	strcpy(this->faceL, "<-");
	strcat(this->faceL, face);

	strcpy(this->faceR, face);
	strcat(this->faceR, "->");

	char buffer[3];
	_itoa(hp, buffer, 10);
	strcat(life, buffer);

	SetFace(this->faceL);
	dir = DIRECTION::ELeft;
}


Character::~Character()
{
}

void Character::Update(int c)
{
	switch (dir)
	{
	case Character::DIRECTION::ELeft:
		if (GetFace() == this->faceL) break;

		SetFace(this->faceL);
		break;
	case Character::DIRECTION::ERight:
		if (GetFace() == this->faceR) break;

		SetFace(this->faceR);
		break;
	}
}


