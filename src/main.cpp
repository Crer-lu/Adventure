#pragma once
#include"castle.h"

int main() {
	//����һ������Ǳ���ÿ����ĸ������ϸ������䷿��
	castle GameCastle(3, 3);
	GameCastle.GenerateRoom();

	//For test: ����Ǳ��ṹͼ
	//GameCastle.PrintMap();

	//��ʽ��ʼ������Ϸ
	GameCastle.PlayGame();
	return 0;
}