#pragma once
class ScoreBoard
{
public:
	ScoreBoard(Screen * screen);
	~ScoreBoard();

	void Update();
	void Render();
	void Initialize();

	void SetEnemyDestroyed(int val);
	void SetScore();
private:
	Screen * screen;

	float playTime;
	int enemyDestroyed;

	char scoreTop[60];
	char scoreBottom[30];
};

