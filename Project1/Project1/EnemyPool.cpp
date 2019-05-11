#include "stdafx.h"
#include "EnemyPool.h"
#include "Enemy.h"
#include "BulletPool.h"



EnemyPool::EnemyPool(int size, Screen * screen)
	: screen(screen)
{
	for (int i = 0; i < size; i++)
	{
		Enemy * enemy = new Enemy("(*__*)", 60, 5, screen);
		enemy->SetActive(false);

		pool.emplace_back(enemy);
	}


	poolIter = pool.begin(); poolIter++;

	head = pool.front();
	{
		for (poolIter; poolIter != pool.end(); poolIter++)
		{
			head->SetNext(*poolIter);
			head = *poolIter;
		}

		tail = head;

		poolIter--;
		for (poolIter; poolIter != pool.begin(); poolIter--)
		{
			head->SetPrev(*poolIter);
			head = *poolIter;
		}
		//poolIter--;
		head->SetPrev(*poolIter);
	}
	head = pool.front();
}


EnemyPool::~EnemyPool()
{
	for (Enemy * enemy : activePool)
		delete enemy;
	activePool.clear();

	for (Enemy * enemy : pool)
		delete enemy;
	pool.clear();
}

void EnemyPool::Update()
{
	activePool.remove_if(bind(&EnemyPool::Predicate, this, std::placeholders::_1));

	for (Enemy * enemy : activePool)
	{
		enemy->Update();
	}
}

void EnemyPool::Draw()
{
	for (Enemy * enemy : activePool)
	{
		enemy->Draw();
	}
}

void EnemyPool::Spawn()
{
	if (head->GetNext() == nullptr) return;

	head->Spawn(rand() % screen->ScreenSize() - 1, 5);

	activePool.emplace_front(head);
	head = head->GetNext();
	pool.remove(activePool.front());
}

void EnemyPool::Collision(BulletPool * bullets)
{
	for (Enemy * enemy : activePool)
	{
		bullets->Collision(enemy);
	}
}

void EnemyPool::Attack(Character * character)
{
	for (Enemy * enemy : activePool)
	{
		int enemyPos = enemy->GetPosition();
		int charPos = character->GetPosition();

		if(abs(enemyPos - charPos) <= 5)
			enemy->Attack(character);
	}
}

bool EnemyPool::Predicate(Enemy * enemy)
{
	bool remove = enemy->IsDead();

	if (remove == true)
	{
		if (enemy->GetPrev() != nullptr)
		{
			enemy->GetPrev()->SetNext(enemy->GetNext());
			enemy->SetNext(nullptr);
		}
		else
		{
			enemy->SetNext(nullptr);
		}

		pool.emplace_back(enemy);

		tail->SetNext(enemy);
		enemy->SetPrev(tail);
		tail = tail->GetNext();
	}

	return remove;
}
