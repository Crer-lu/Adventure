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
	int numOfLevel;//�Ǳ��Ĳ���
	int numOfEachLevel;//ÿ��Ǳ��ķ��������ķ�֮һ����Ϊ������ĸ��Ƿֲ���
	int princessLevel, monsterLevel;
	lobbyRoom* startPosition = NULL;
};