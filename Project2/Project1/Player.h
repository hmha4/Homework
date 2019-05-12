#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(const char * face, int position, unsigned int hp, Screen * screen);
	~Player();

	// Character을(를) 통해 상속됨
	virtual void Update(int c = 0);
	virtual void Draw() override;
	void Initialize();

	bool IsFire() { return isFire; }
	bool IsLaser() { return isLaser; }
	void UpdateLaserInfo(float duration, float coolTime);

private:
	void LaserControl();
	void Reload();
	void UpdateGunInfo();
	void ShowInfo();
private:
	bool isFire;
	int bulletCount;
	int maxBullet;
	bool reload;
	float reloadTimePerBullet;

	bool isLaser;
	float laserDuration;
	float laserCoolDown;

	char infoGun[30];
	char infoLaser[30];
	char * info;
	float showInfoTime;
};

