#pragma once
#include<stddef.h>
//用来区分房间的位置
enum LOCATION_TYPE {
	INNER = 1,
	WESTEST,
	EASTEST,
	LOBBY
};
//用来区分房间的功能类型
enum FUNCTION_TYPE {
	FUNC_NORMAL = 1,
	FUNC_LOBBY,
	FUNC_MONSTER,
	FUNC_PRINCESS,
	FUNC_MESSAGE,
	FUNC_TRANS
};
//用来区分信息房的信息类型
enum MESSAGE_TYPE {
	MES_PRINCESS = 1,
	MES_MONSTER
};
//用来移动位置，对应每一个可能的合法方向
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
//定义room基类
class room {
public:
	room(const int& loc_type, const int& func_type) : locationType(loc_type), functionType(func_type) {};
	~room() {};
	virtual void PrintSteps();
	virtual void PrintMessage() = 0;//pure virtual function
	//执行移动的指令
	virtual room* Execute(int);
	//获取private修饰过的基础属性
	int GetFunctionType() { return functionType; };
	int GetLocatinoType() { return locationType; };
	//room拥有的基础属性，进入房间后三个可能的运动方向
	//如果为空则表明位于最西边或者最东边，即已经运动到了楼层尽头
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
	void PrintSteps();//overide 重写PrintSteps函数
	room* Execute(int);//overide 重写Execute函数
	void PrintMessage();//PrintMessage函数
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
	void PrintMessage();//PrintMessage函数
private:

};
class monsterRoom : public room {
public:
	monsterRoom(const int& loc_type) : room(loc_type, FUNC_MONSTER) {};
	~monsterRoom() {};
	void PrintMessage();//PrintMessage函数
private:

};

class princessRoom : public room {
public:
	princessRoom(const int& loc_type) : room(loc_type, FUNC_PRINCESS) { status = 1; };
	~princessRoom() {};
	void PrintMessage();//PrintMessage函数
	void SetStatus() { status = 0; };
	int GetStatus() { return status; };
private:
	//status = 0 已经到过该房间 status = 1 还没有到过该房间
	//用于当玩家区分玩家是否第一次到达公主房
	int status;
};

class transRoom : public room {
public:
	transRoom(const int& loc_type) : room(loc_type, FUNC_TRANS) {};
	~transRoom() {};
	void PrintMessage();//PrintMessage函数
	void PrintSteps();//overide 重写PrintSteps函数
	room* Execute(int);//overide 重写Execute函数
	//设置传送门的目标房间
	void SetDestination(room* des) { destinationRoom = des ;};
private:
	room* destinationRoom = NULL;
};

class messageRoom : public room {
public:
	messageRoom(const int& loc_type, const int& mes_type) : room(loc_type, FUNC_MESSAGE), messageType(mes_type) {};
	~messageRoom() {};
	void PrintMessage();//PrintMessage函数
	void SetMessage(int);
private:
	int messageType;//总共两种信息，一种是Monster所在的level，一种是pricess所在的level
	int level;
};