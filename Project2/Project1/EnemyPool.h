#pragma once
class EnemyPool
{
public:
	EnemyPool(int size, Screen * screen);
	~EnemyPool();

	void Update();
	void Draw();
	void Initialize();

	void Spawn();

	int GetEnemyKilled() { return enemyKilled; }
	void Collision(class BulletPool * bullets);
	void Attack(class Character * character);
	class Enemy * GetNearest(class Character * character);
private:
	bool Predicate(class Enemy* enemy);
	void Remove(class Enemy* enemy);
private:
	class Player * player;

	list<class Enemy*> pool;
	list<class Enemy*> activePool;

	list<class Enemy*>::iterator poolIter;
	list<class Enemy*>::iterator activePoolIter;

	class Enemy* head;
	class Enemy* tail;

	int enemyKilled;

	Screen* screen;
};

