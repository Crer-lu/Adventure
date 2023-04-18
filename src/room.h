#pragma once
#include<stddef.h>
enum LOCATION_TYPE {
	INNER = 1,
	WESTEST,
	EASTEST,
	LOBBY
};
enum FUNCTION_TYPE {
	FUNC_NORMAL = 1,
	FUNC_LOBBY,
	FUNC_MONSTER,
	FUNC_PRINCESS,
	FUNC_MESSAGE,
	FUNC_TRANS
};
enum MESSAGE_TYPE {
	MES_PRINCESS = 1,
	MES_MONSTER
};
enum DIRECTION {
	WEST = 1,
	EAST,
	OPPOSITE,
	SOUTHEAST,
	SOUTHWEST,
	NORTHEAST,
	NORTHWEST,
	UP,
	DOWN,
	TRANS
};
class room {
public:
	room(const int& loc_type, const int& func_type) : locationType(loc_type), functionType(func_type) {};
	~room() {};
	void PrintSteps();
	int GetFunctionType() { return functionType; };
	int GetLocatinoType() { return locationType; };
	room* Execute(int);
	room* oppositeRoom = NULL;
	room* westRoom = NULL;
	room* eastRoom = NULL;

private:
	const int functionType;
	const int locationType;
};

class lobbyRoom : public room {
public:
	lobbyRoom(const int& loc_type, const int& lev) : room(loc_type, FUNC_LOBBY), level(lev) {};
	~lobbyRoom() {};
	void PrintSteps();//重写PrintSteps函数
	room* Execute(int);//重写Execute函数
	void PrintMessage();
	int GetLevel() { return level; };
	room* southeastRoom = NULL;
	room* southwestRoom = NULL;
	room* northeastRoom = NULL;
	room* northwestRoom = NULL;
	room* up = NULL;
	room* down = NULL;
private:
	const int level;
};
class normalRoom : public room {
public:
	normalRoom(const int& loc_type) : room(loc_type, FUNC_NORMAL) {};
	~normalRoom() {};
	void PrintMessage();
private:

};
class monsterRoom : public room {
public:
	monsterRoom(const int& loc_type) : room(loc_type, FUNC_MONSTER) {};
	~monsterRoom() {};
	void PrintMessage();
private:

};

class princessRoom : public room {
public:
	princessRoom(const int& loc_type) : room(loc_type, FUNC_PRINCESS) { status = 1; };
	~princessRoom() {};
	void PrintMessage();
	void SetStatus() { status = 0; };
	int GetStatus() { return status; };
private:
	int status;
};

class transRoom : public room {
public:
	transRoom(const int& loc_type) : room(loc_type, FUNC_TRANS) {};
	~transRoom() {};
	void PrintMessage();
	void PrintSteps();
	room* Execute(int);//重写Execute函数
	void SetDestination(room* des) { destinationRoom = des ;};
private:
	room* destinationRoom = NULL;
};

class messageRoom : public room {
public:
	messageRoom(const int& loc_type, const int& mes_type) : room(loc_type, FUNC_MESSAGE), messageType(mes_type) {};
	~messageRoom() {};
	void PrintMessage();
	void SetMessage(int);
private:
	int messageType;
	int level;
};