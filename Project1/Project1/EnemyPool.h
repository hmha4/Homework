#pragma once
class EnemyPool
{
public:
	EnemyPool(int size, Screen * screen);
	~EnemyPool();

	void Update();
	void Draw();

	void Spawn();
	void Collision(class BulletPool * bullets);
	void Attack(class Character * character);
private:
	bool Predicate(class Enemy* enemy);
private:
	list<class Enemy*> pool;
	list<class Enemy*> activePool;

	list<class Enemy*>::iterator poolIter;
	list<class Enemy*>::iterator activePoolIter;

	class Enemy* head;
	class Enemy* tail;

	Screen* screen;
};

