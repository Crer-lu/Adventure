#pragma once
#include<stdio.h>
#include<iostream>
#include"castle.h"

int main() {
	castle GameCastle(3, 3);
	GameCastle.GenerateRoom();
	//GameCastle.PrintMap();
	GameCastle.PlayGame();
	return 0;
}