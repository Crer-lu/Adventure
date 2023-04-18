#pragma once
#include "room.h"
class castle {
public:
	castle(const int& hei, const int& each) : numOfLevel(hei), numOfEachLevel(each) {};
	~castle() {};
	void GenerateRoom();
	void PrintMap();
	void PlayGame();
	void GameOver(int);
private:
	int numOfLevel;//城堡的层数
	int numOfEachLevel;//每层城堡的房间数的四分之一（因为房间分四个角分布）
	int princessLevel, monsterLevel;
	lobbyRoom* startPosition = NULL;
};