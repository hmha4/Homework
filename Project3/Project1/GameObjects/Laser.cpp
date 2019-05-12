#include "../stdafx.h"
#include "Laser.h"
#include "Character.h"
#include "Player.h"



Laser::Laser(const char * face, Screen * screen)
	: GameObject(-1, face, screen)
	, length(64), laserOn(false)
	, duration(0.0f), coolTime(0.0f), attackTime(0.0f)
{
	SetActive(false);
	CreateBuffer();
}


Laser::~Laser()
{
	delete[] buffer;
}

void Laser::Update()
{	
	if(laserOn == false) return;

	if (duration >= maxDur)
	{
		SetActive(false);
		coolTime += Time::Get()->Delta();

		if (coolTime >= maxCool)
		{
			duration = 0.0f;
			coolTime = 0.0f;

			laserOn = false;
		}
	}
	else
	{
		duration += Time::Get()->Delta();

		attackTime += Time::Get()->Delta();
		if (attackTime >= 1.0f)
		{
			attackTime = 0.0f;
			target->SetHP(target->GetHP() - 1);
			if (target->GetHP() <= 0)
			{
				SetActive(false);
				duration = maxDur;
				return;
			}
		}
	}

	Player * player = dynamic_cast<Player*>(start);
	if (player != nullptr)
		player->UpdateLaserInfo(maxDur - duration, maxCool - coolTime);

	if (GetActive() == false) return;

	int startPos = (start->GetPosition() + (start->GetPosition() + start->GetFaceSize())) / 2;
	SetPosition(startPos);

	int targetPos = (target->GetPosition() + (target->GetPosition() + target->GetFaceSize())) / 2;
	int dir = startPos - targetPos;
	if (dir > 0)
		SetPosition(targetPos);

	int size = abs(dir);

	Clear();
	if (size > 0)
	{
		char temp[64]{ '\0' };
		for (int i = 0; i < size; i++)
			strcat(temp, "-");
		temp[size - 1] = '\0';
		strcpy(buffer, temp);
	}
	SetFace(buffer);

	
}

void Laser::Clear()
{
	for (int i = 0; i < length; i++)
		buffer[i] = ' ';
	buffer[length - 1] = '\0';
}

void Laser::CreateBuffer()
{
	buffer = new char[length];
	for (int i = 0; i < length; i++)
		buffer[i] = ' ';
	buffer[length - 1] = '\0';
}

void Laser::Fire(Character * start, Character * target, float duration, float coolTime)
{
	SetActive(true);
	laserOn = true;

	this->start = start;
	this->target = target;

	maxDur = duration;
	maxCool = coolTime;
}
