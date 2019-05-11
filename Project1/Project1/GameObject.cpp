#include "stdafx.h"
#include "GameObject.h"
#include "Character.h"


GameObject::GameObject(int pos, const char * face, Screen* screen)
	:pos(pos), screen(screen), isActive(true)
{
	this->face = face;
	strcpy(life, "HP : ");
}


GameObject::~GameObject()
{
}

void GameObject::Draw()
{
	if (screen == nullptr) return;
	if (isActive == false) return;
	if (pos < 0 || pos > screen->ScreenSize()) return;

	screen->Draw1(pos, face);
	Character * character = dynamic_cast<Character*>(this);
	if (character != nullptr)
	{
		screen->Draw2(pos, life);
	}
}
