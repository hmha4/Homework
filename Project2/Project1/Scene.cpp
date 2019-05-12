#include "stdafx.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletPool.h"
#include "EnemyPool.h"
#include "ScoreBoard.h"


Scene::Scene(Screen * screen)
	: screen(screen)
	, spawnTime(0.0f)
{
	state = STATE::PLAY;
}


Scene::~Scene()
{
	delete player;
	delete enemies;
	delete bullets;
	delete score;
}

void Scene::Initialize()
{
	player = new Player("(^__^)", 20, 10, screen);
	enemies = new EnemyPool(5, screen);
	bullets = new BulletPool(100, screen);
	score = new ScoreBoard(screen);
}

void Scene::Update(int c)
{
	switch (state)
	{
	case Scene::STATE::PLAY:
	{
		if (player->GetHP() <= 0)
		{
			state = STATE::END;
			score->SetEnemyDestroyed(enemies->GetEnemyKilled());
			score->SetScore();
			break;
		}

		spawnTime += Time::Get()->Delta();
		if (spawnTime >= 2.0f)
		{
			enemies->Spawn();
			spawnTime = 0.0f;
		}

		player->Update(c);

		if (player->IsLaser() == true && player->IsFire() == true)
		{
			Enemy * enemy = enemies->GetNearest(player);
			bullets->FireLaser(player, enemy, 2.0f, 3.0f);
		}
		else if (player->IsFire() == true)
			bullets->Fire(player);

		bullets->Update();

		enemies->Update();
		enemies->Collision(bullets);
		enemies->Attack(player);

		score->Update();

		break;
	}
	case Scene::STATE::END:
		if (c == 'r')
			Restart();
		break;
	default:
		break;
	}
	
}

void Scene::Render()
{
	switch (state)
	{
	case Scene::STATE::PLAY:
	{
		bullets->Draw();
		player->Draw();
		enemies->Draw();
		break;
	}
	case Scene::STATE::END:
		score->Render();
		

		break;
	default:
		break;
	}
}

void Scene::Restart()
{
	player->Initialize();
	enemies->Initialize();
	bullets->Initialize();
	score->Initialize();
	spawnTime = 0.0f;
	state = STATE::PLAY;
}
