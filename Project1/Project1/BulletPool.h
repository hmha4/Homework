#pragma once
class BulletPool
{
public:
	BulletPool(int size, Screen * screen);
	~BulletPool();

	void Update();
	void Draw();

	void Fire(class Character * character);
	void Collision(class Character * character);

private:
	bool Predicate(class Bullet* bullet);
private:
	list<class Bullet*> pool;
	list<class Bullet*> activePool;

	list<class Bullet*>::iterator poolIter;
	list<class Bullet*>::iterator activePoolIter;

	class Bullet* head;
	class Bullet* tail;
};

