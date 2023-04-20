#pragma once
#include"castle.h"

int main() {
	//创建一个三层城堡，每层的四个方向上各有三间房间
	castle GameCastle(3, 3);
	GameCastle.GenerateRoom();

	//For test: 输出城堡结构图
	//GameCastle.PrintMap();

	//正式开始运行游戏
	GameCastle.PlayGame();
	return 0;
}