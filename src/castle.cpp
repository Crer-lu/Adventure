#pragma once
#include<cstdlib>
#include<time.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include "castle.h"
#include "room.h"
using namespace std;

void Replace(room* now, room* old) {
	now->eastRoom = old->eastRoom;
	now->westRoom = old->westRoom;
	now->oppositeRoom = old->oppositeRoom;
	if (old->eastRoom)
	{
		if (old->eastRoom->GetFunctionType() != FUNC_LOBBY) old->eastRoom->westRoom = now;
		else {
			lobbyRoom* lob = (lobbyRoom*)old->eastRoom;
			if (lob->northwestRoom == old) lob->northwestRoom = now;
			else lob->southwestRoom = now;
		}
	}
	if (old->westRoom) {
		if (old->westRoom->GetFunctionType() != FUNC_LOBBY) old->westRoom->eastRoom = now;
		else {
			lobbyRoom* lob = (lobbyRoom*)old->westRoom;
			if (lob->northeastRoom == old) lob->northeastRoom = now;
			else lob->southeastRoom = now;
		}
	}
	if (old->oppositeRoom) old->oppositeRoom->oppositeRoom = now;
	return;
}
//用一个vector存下所有普通节点的地址值，用于添加特殊节点
//另外，可以用来结束游戏时delete释放内存
vector< pair<room*, int> >vec_room;
void castle::GenerateRoom() {
	srand(time(NULL));
	//是否已经用过某个ID值，用于独一无二地确定一个图
	int num_of_room = numOfEachLevel * numOfLevel * 4;
	int* is_used = new int[num_of_room]{0};
	//外循环：生成楼道的房间lobbyRoom
	lobbyRoom* last = NULL;
	for (int i = 1; i <= numOfLevel; ++i) {
		lobbyRoom* lob = new lobbyRoom(LOBBY, i);
		lob->down = last;
		if (last) last->up = lob;
		//内循环：生成每一层的房间 四个方向各numOfEachLevel	
		room * last_southeast = lob,* last_southwest = lob, * last_northeast = lob, * last_northwest = lob;
		for (int j = 1; j <= numOfEachLevel; ++j) {
			//申请相应的节点空间
			normalRoom* southeast, *southwest, *northeast, *northwest;
			if (j != numOfEachLevel) {
				southeast = new normalRoom(INNER); vec_room.push_back(make_pair(southeast, INNER));
				southwest = new normalRoom(INNER); vec_room.push_back(make_pair(southwest, INNER));
				northeast = new normalRoom(INNER); vec_room.push_back(make_pair(northeast, INNER));
				northwest = new normalRoom(INNER); vec_room.push_back(make_pair(northwest, INNER));
			}
			else {
				southeast = new normalRoom(EASTEST); vec_room.push_back(make_pair(southeast, EASTEST));
				southwest = new normalRoom(WESTEST); vec_room.push_back(make_pair(southwest, WESTEST));
				northeast = new normalRoom(EASTEST); vec_room.push_back(make_pair(northeast, EASTEST));
				northwest = new normalRoom(WESTEST); vec_room.push_back(make_pair(northwest, WESTEST));
			}
			if (j == 1) {
				lob->northeastRoom = northeast;
				lob->northwestRoom = northwest;
				lob->southeastRoom = southeast;
				lob->southwestRoom = southwest;
			}
			southeast->westRoom = last_southeast;
			southeast->oppositeRoom = northeast;
			last_southeast->eastRoom = southeast;
			southwest->eastRoom = last_southwest;
			southwest->oppositeRoom = northwest;
			last_southwest->westRoom = southwest;
			northwest->eastRoom = last_northwest;
			northwest->oppositeRoom = southwest;
			last_northwest->westRoom = northwest;
			northeast->westRoom = last_northeast;
			northeast->oppositeRoom = southeast;
			last_northeast->eastRoom = northeast;

			last_northeast = northeast;
			last_northwest = northwest;
			last_southeast = southeast;
			last_southwest = southwest;
		}
		last = lob;
		if (i == 1) startPosition = lob;
	}
	//开始把特殊房间替换到刚刚生成的图中
	
	//TransRoom
	//生成两个不相等的数字 范围是[0, num_of_room)
	int a, b;
	do { a = rand() % num_of_room; } while (is_used[a] == 1);
	is_used[a] = 1;
	do { b = rand() % num_of_room; } while (is_used[b] == 1);
	is_used[b] = 1;
	//申请空间，开始替换
	transRoom* rooma = new transRoom(vec_room[a].second);
	transRoom* roomb = new transRoom(vec_room[b].second);
	rooma->SetDestination(roomb);
	roomb->SetDestination(rooma);
	Replace(rooma, vec_room[a].first);
	Replace(roomb, vec_room[b].first);

	//MonsterRoom

	//生成一个数字，设置为怪兽房间
	do { a = rand() % num_of_room; } while (is_used[a] == 1);
	is_used[a] = 1;
	int mon_level = a / (numOfEachLevel * 4) + 1;
	monsterRoom* mons = new monsterRoom(vec_room[a].second);
	Replace(mons, vec_room[a].first);

	//PrincessRoom
	do { a = rand() % num_of_room; } while (is_used[a] == 1);
	is_used[a] = 1;
	int pri_level = a / (numOfEachLevel * 4) + 1;
	princessRoom* prin = new princessRoom(vec_room[a].second);
	Replace(prin, vec_room[a].first);

	//MessageRoom

	//生成两个不同的数字，并且分别设置为公主和怪兽的信息房
	do { a = rand() % num_of_room; } while (is_used[a] == 1);
	is_used[a] = 1;
	do { b = rand() % num_of_room; } while (is_used[b] == 1);
	is_used[b] = 1;

	messageRoom* room_princess = new messageRoom(vec_room[a].second, MES_PRINCESS);
	room_princess->SetMessage(pri_level);
	Replace(room_princess, vec_room[a].first);
	messageRoom* room_monster = new messageRoom(vec_room[b].second, MES_MONSTER);
	room_monster->SetMessage(mon_level);
	Replace(room_monster, vec_room[b].first);
	return;
}

void PrintDirection(room* start, int dir) {
	int id = 0;
	while (start) {
		switch (start->GetFunctionType()) {
		case FUNC_MESSAGE:
			printf("room%d : Message Room \n", id);
			break;
		case FUNC_MONSTER:
			printf("room%d : Monster Room \n", id);
			break;
		case FUNC_NORMAL:
			//printf("room%d : Normal Room \n", id);
			break;
		case FUNC_PRINCESS:
			printf("room%d : Princess Room \n", id);
			break;
		case FUNC_TRANS:
			printf("room%d : Tranmittable Room\n", id);
			break;
		default:
			break;
		}
		id++;
		//dir == 0 -> west
		//dir == 1 -> east
		if (dir) start = start->eastRoom;
		else start = start->westRoom;
	}
}
void castle::PrintMap() {
	lobbyRoom* floor = startPosition;
	while (floor != NULL) {
		printf("floor %d\n", floor->GetLevel());
		printf("Southeast: \n");
		PrintDirection(floor->southeastRoom, 1);
		printf("Southwest: \n");
		PrintDirection(floor->southwestRoom, 0);
		printf("Northeast: \n");
		PrintDirection(floor->northeastRoom, 1);
		printf("Northwest: \n");
		PrintDirection(floor->northwestRoom, 0);
		floor = (lobbyRoom*)floor->up;
	}
	return;
}
int StepToNumber() {
	string dir;
	getline(cin, dir);
	if (dir.size() < 4) return 0;
	dir = dir.substr(3);
	transform(dir.begin(), dir.end(), dir.begin(), ::toupper);
	if (dir == "WEST") return WEST;
	else if (dir == "EAST") return EAST;
	else if (dir == "OPPOSITE") return OPPOSITE;
	else if (dir == "SOUTHEAST") return SOUTHEAST;
	else if (dir == "SOUTHWEST") return SOUTHWEST;
	else if (dir == "NORTHEAST") return NORTHEAST;
	else if (dir == "NORTHWEST") return NORTHWEST;
	else if (dir == "UP") return UP;
	else if (dir == "DOWN") return DOWN;
	else if (dir == "TRANS") return TRANS;
	else return 0;//Error Code
}
void castle::PlayGame() {
	puts("CLI GAME : ADVENTURE");
	puts("You are the hero! Please find the princess in the castle and take her out of here!");
	puts("Instruction Example: [go east]");
	int flag = 0;//初始状态：没接到公主
	room* last = startPosition;
	lobbyRoom* lob;
	messageRoom* mes;
	monsterRoom* mon;
	normalRoom* nor;
	princessRoom* pri;
	transRoom* tra;
	while (1) {
		if (last == startPosition && flag) {
			GameOver(1);
		}
		room* temp;//存放临时值
		switch (last->GetFunctionType()) {
		case FUNC_LOBBY:
			lob = (lobbyRoom*)last;
			lob->PrintMessage();
			lob->PrintSteps();
			if (temp = lob->Execute(StepToNumber())) last = temp;
			else puts("INSTRUCTION ERROR !!!");
			break;
		case FUNC_MESSAGE:
			mes = (messageRoom*)last;
			mes->PrintMessage();
			mes->PrintSteps();
			if (temp = mes->Execute(StepToNumber())) last = temp;
			else puts("INSTRUCTION ERROR !!!");
			break;
		case FUNC_MONSTER:
			mon = (monsterRoom*)last;
			mon->PrintMessage();
			GameOver(0);
			break;
		case FUNC_NORMAL:
			nor = (normalRoom*)last;
			nor->PrintMessage();
			nor->PrintSteps();
			if (temp = nor->Execute(StepToNumber())) last = temp;
			else puts("INSTRUCTION ERROR !!!");
			break;
		case FUNC_PRINCESS:
			pri = (princessRoom*)last;
			pri->PrintMessage();
			pri->SetStatus();
			flag = 1;
			pri->PrintSteps();
			if (temp = pri->Execute(StepToNumber())) last = temp;
			else puts("INSTRUCTION ERROR !!!");
			break;
		case FUNC_TRANS:
			tra = (transRoom*)last;
			tra->PrintMessage();
			tra->PrintSteps();
			if (temp = tra->Execute(StepToNumber())) last = temp;
			else puts("INSTRUCTION ERROR !!!");
			break;
		default:
			cout << "UNEXPECTED ERROR!" << endl;
			break;
		}
	}
	return;
}

void castle::GameOver(int res) {
	if (res) puts("WIN!");
	else puts("LOSE!");
	system("pause");
	exit(0);
	return;
}