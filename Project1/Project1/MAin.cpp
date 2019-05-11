#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletPool.h"
#include "EnemyPool.h"

int main()
{
	const int screen_size = 80;

	Screen * screen = new Screen(screen_size);
	Player * player = new Player( "(^__^)", 20, 10, screen);
	EnemyPool * enemies = new EnemyPool(5, screen);
	BulletPool * bullets = new BulletPool(100, screen);

	float spawnTime = 0.0f;

	while (true)
	{
		int c = -1;
		//	_getche : echo
		if (_kbhit())
		{
			c = _getch();	//	blocking ÇÔ¼ö
		}

		//	Update
		{
			spawnTime += 0.016f;
			if (spawnTime >= 2.0f)
			{
				enemies->Spawn();
				spawnTime = 0.0f;
			}

			player->Update(c);

			if (player->IsFire() == true)
				bullets->Fire(player);
			bullets->Update();

			enemies->Update();
			enemies->Collision(bullets);
			enemies->Attack(player);
		}

		//	Clear
		screen->Clear();

		//	Render
		{
			player->Draw();
			enemies->Draw();
			bullets->Draw();
		}
		screen->Render();

		Sleep(66);
	}

	delete screen;
	delete player;
	delete enemies;
	delete bullets;

	return 0;
}