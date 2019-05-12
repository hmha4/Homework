#pragma once
class Scene
{
public:
	Scene(Screen * screen);
	~Scene();

	void Initialize();
	void Update(int c);
	void Render();

private:
	void Restart();

private:
	enum class STATE
	{
		PLAY,
		END
	} state;
private:
	Screen * screen;
	float spawnTime;

	class Player * player;
	class EnemyPool * enemies;
	class BulletPool * bullets;
	class ScoreBoard * score;
};

