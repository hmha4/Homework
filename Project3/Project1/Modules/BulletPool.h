#pragma once
class BulletPool
{
public:
	BulletPool(int size, Screen * screen);
	~BulletPool();

	void Update();
	void Draw();
	void Initialize();

	void Fire(class Character * character);
	void FireLaser(class Character * start, class Character * target, float duration = 2.0f, float coolTime = 3.0f);

	void Collision(class Character * character);

private:
	bool Predicate(class Bullet* bullet);
	void Remove(class Bullet* bullet);
private:
	list<class Bullet*> pool;
	list<class Bullet*> activePool;

	list<class Bullet*>::iterator poolIter;
	list<class Bullet*>::iterator activePoolIter;

	class Bullet* head;
	class Bullet* tail;

	class Laser* laser;
};

