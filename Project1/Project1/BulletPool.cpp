#include "stdafx.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "Character.h"



BulletPool::BulletPool(int size, Screen * screen)
{
	for (int i = 0; i < size; i++)
		pool.emplace_back(new Bullet("+", screen));


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
		head->SetPrev(*poolIter);
	}
	head = pool.front();
}


BulletPool::~BulletPool()
{
	for (Bullet * bullet : activePool)
		delete bullet;
	activePool.clear();

	for (Bullet * bullet : pool)
		delete bullet;
	pool.clear();
}

void BulletPool::Update()
{
	activePool.remove_if(bind(&BulletPool::Predicate, this, std::placeholders::_1));

	for (Bullet * bullet : activePool)
	{
		bullet->Update();
	}
}

void BulletPool::Draw()
{
	for (Bullet * bullet : activePool)
	{
		bullet->Draw();
	}
}

void BulletPool::Fire(Character * character)
{
	if (head->GetNext() == nullptr) return;

	head->Fire(character);

	activePool.emplace_front(head);
	head = head->GetNext();
	pool.remove(activePool.front());
}

void BulletPool::Collision(Character * character)
{
	for (Bullet * bullet : activePool)
	{
		bullet->Collision(character);
	}
}

bool BulletPool::Predicate(Bullet* bullet)
{
	bool remove = bullet->GetActive();

	if (remove == false)
	{
		if (bullet->GetPrev() != nullptr)
		{
			bullet->GetPrev()->SetNext(bullet->GetNext());
			bullet->SetNext(nullptr);
		}
		else
		{
			bullet->SetNext(nullptr);
		}

		pool.emplace_back(bullet);

		tail->SetNext(bullet);
		tail = tail->GetNext();
	}

	return !remove;
}
