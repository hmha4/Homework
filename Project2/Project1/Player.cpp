#include "stdafx.h"
#include "Player.h"
#include "Render.h"


Player::Player(const char * face, int position, unsigned int hp, Screen * screen)
	: Character(face, position, hp, screen)
	, isFire(false), bulletCount(10), maxBullet(10)
	, reload(false), reloadTimePerBullet(0.0f)
	, isLaser(false), laserDuration(0.0f), laserCoolDown(0.0f)
	, showInfoTime(FLT_MAX)
{
	UpdateGunInfo();
	UpdateLaserInfo(2.0f, 3.0f);
	info = infoGun;
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
		showInfoTime = 0.0f;
		
		if (isLaser == false)
		{
			if (bulletCount > 0)
				isFire = true;

			reload = false;
			bulletCount--;
			if (bulletCount <= 0)
			{
				reload = true;
				bulletCount = 0;
			}

			UpdateGunInfo();
		}
		else isFire = true;

		break;
	case 'm':
		isLaser = !isLaser;
		if (isLaser == true)
			info = infoLaser;
		else
			info = infoGun;
	}

	Reload();

	if (GetPosition() + GetFaceSize() > GetScreenSize())
		SetPosition(GetScreenSize() - (int)GetFaceSize());
	if (GetPosition() < 0)
		SetPosition(0);

	__super::Update();
}

void Player::Draw()
{
	__super::Draw();
	ShowInfo();
}

void Player::Initialize()
{
	isFire = false;
	bulletCount = 10;
	maxBullet = 10;
	reload = false;
	reloadTimePerBullet = 0.0f;
	isLaser = false;
	laserDuration = 0.0f;
	laserCoolDown = 0.0f;
	showInfoTime = FLT_MAX;
	
	UpdateGunInfo();
	UpdateLaserInfo(2.0f, 3.0f);
	info = infoGun;
}

void Player::UpdateLaserInfo(float duration, float coolTime)
{
	char buffer[10];
	_itoa((int)duration, buffer, 10);
	strcpy(infoLaser, buffer);
	strcat(infoLaser, ".");
	int decimal = (int)((duration - (int)duration) * 100);
	_itoa((int)decimal, buffer, 10);
	strcat(infoLaser, buffer);
	strcat(infoLaser, "/");
	_itoa((int)coolTime, buffer, 10);
	strcat(infoLaser, buffer);
	strcat(infoLaser, ".");
	decimal = (int)((coolTime - (int)coolTime) * 100);
	_itoa((int)decimal, buffer, 10);
	strcat(infoLaser, buffer);
	strcat(infoLaser, "\0");
}

void Player::LaserControl()
{
	if (isLaser == true)
	{
		if (laserDuration >= 2.0f)
		{
			isFire = false;

			laserCoolDown += 0.016f;
			if (laserCoolDown >= 3.0f)
			{
				laserDuration = 0.0f;
				laserCoolDown = 0.0f;
			}
		}
		else
		{
			laserDuration += 0.016f;
		}
	}
}

void Player::Reload()
{
	if (reload == true)
	{
		reloadTimePerBullet += Time::Get()->Delta();
		if (reloadTimePerBullet >= 1.0f)
		{
			bulletCount++;
			reloadTimePerBullet = 0.0f;
			UpdateGunInfo();

			if (bulletCount >= maxBullet)
			{
				bulletCount = maxBullet;
				reload = false;
			}
		}
	}
}

void Player::UpdateGunInfo()
{
	char buffer[3];
	_itoa(bulletCount, buffer, 10);
	strcpy(infoGun, buffer);
	strcat(infoGun, "/");
	_itoa(maxBullet, buffer, 10);
	strcat(infoGun, buffer);
	strcat(infoGun, "\0");
}

void Player::ShowInfo()
{
	if (showInfoTime >= 1.0f) return;
	showInfoTime += Time::Get()->Delta();

	int pos = 0;
	if (GetDirection() == DIRECTION::ELeft)
		pos = GetPosition() + GetFaceSize() + 1;
	else
	{
		int size = (int)strlen(info);
		pos = GetPosition() - size - 1;
	}

	GetScreen()->Draw1(pos, info);
}
