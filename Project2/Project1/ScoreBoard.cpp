#include "stdafx.h"
#include "ScoreBoard.h"



ScoreBoard::ScoreBoard(Screen * screen)
	: screen(screen)
	, playTime(0.0), enemyDestroyed(0)
{
	SetScore();
}


ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::Update()
{
	playTime += Time::Get()->Delta();
}

void ScoreBoard::Render()
{
	screen->Draw1(0, scoreTop);
	screen->Draw2(0, scoreBottom);
}

void ScoreBoard::Initialize()
{
	playTime = 0.0f;
	enemyDestroyed = 0;
	SetScore();
}

void ScoreBoard::SetEnemyDestroyed(int val)
{
	enemyDestroyed = val;
}

void ScoreBoard::SetScore()
{
	//	Top
	{
		char buffer[10];
		strcpy(scoreTop, "Play Time : ");
		_itoa((int)playTime, buffer, 10);
		strcat(scoreTop, buffer);
		strcat(scoreTop, ".");
		int decimal = (int)((playTime - (int)playTime) * 100);
		_itoa((int)decimal, buffer, 10);
		strcat(scoreTop, buffer);
		strcat(scoreTop, "\t\tPress r to Restart...");
	}
	
	//	Bottom
	{
		char buffer[3];
		strcpy(scoreBottom, "Enemy Killed : ");
		_itoa(enemyDestroyed, buffer, 10);
		strcat(scoreBottom, buffer);
	}
}

