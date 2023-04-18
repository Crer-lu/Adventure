#pragma once
#include "room.h"
#include<iostream>
using namespace std;
room* room::Execute(int step) {
	if (step == OPPOSITE) return oppositeRoom;
	else if (step == WEST) {
		if (GetLocatinoType() == WESTEST) return NULL;
		else return westRoom;
	}
	else if (step == EAST) {
		if (GetLocatinoType() == EASTEST) return NULL;
		else return eastRoom;
	}
	else return NULL;
}
room* lobbyRoom::Execute(int step) {
	if (step == UP) return up;
	else if (step == DOWN) return down;
	else if (step == SOUTHEAST) return southeastRoom;
	else if (step == SOUTHWEST) return southwestRoom;
	else if (step == NORTHEAST) return northeastRoom;
	else if (step == NORTHWEST) return northwestRoom;
	else return NULL;
}
room* transRoom::Execute(int step) {
	if (step == OPPOSITE) return oppositeRoom;
	else if (step == WEST) {
		if (GetLocatinoType() == WESTEST) return NULL;
		else return westRoom;
	}
	else if (step == EAST) {
		if (GetLocatinoType() == EASTEST) return NULL;
		else return eastRoom;
	}
	else if (step == TRANS)
		return destinationRoom;
	else return NULL;
}
void room::PrintSteps() {
	switch (locationType)
	{
	case INNER:
		cout << "There are 3 exits: east, west and opposite."<< endl;
		break;
	case WESTEST:
		cout << "There are 2 exits: east and opposite."<< endl;
		break;
	case EASTEST:
		cout << "There are 2 exits: west and opposite."<< endl;
		break;
	default:
		break;
	}
	return;
}

void lobbyRoom::PrintSteps() {
	if (down == NULL) {
		cout << "There are 5 exits: southeast, southwest£¬ northeast, northwest and up." << endl;
	}
	else if (up == NULL) {
		cout << "There are 5 exits: southeast, southwest£¬ northeast, northwest and down." << endl;
	}
	else {
		cout << "There are 6 exits: southeast, southwest£¬ northeast, northwest, up and down." << endl;
	}
	return;
}

void normalRoom::PrintMessage() {
	cout << "This is a normal room" << endl;
	return;
}
void lobbyRoom::PrintMessage() {
	cout << "This is lobby of level " << level << endl;
	return;
}

void monsterRoom::PrintMessage() {
	cout << "Terrible! You meet the monster and the game is over" << endl;
	return;
}

void princessRoom::PrintMessage() {
	if(GetStatus())
		cout << "Congratulations! You find the princess and please take her to the lobby of level 1" << endl;
	else
		cout << "You have taken away the princess.Please take her to the lobby of level 1" << endl;
	return;
}

void transRoom::PrintMessage() {
	cout << "This is a transmissive room and you get another optional room to go : trans" << endl;
	return;
}

void transRoom::PrintSteps() {
	switch (GetLocatinoType())
	{
	case INNER:
		cout << "There are 4 exits: trans, east, west and opposite." << endl;
		break;
	case WESTEST:
		cout << "There are 3 exits: trans, east and opposite." << endl;
		break;
	case EASTEST:
		cout << "There are 3 exits: trans, west and opposite." << endl;
		break;
	default:
		break;
	}
	return;
}
void messageRoom::PrintMessage() {
	cout << "This is a message room and you get a message: ";
	if (messageType == MES_MONSTER) {
		cout << "The monster is on the floor of level " << level<< endl;
	}
	else if (messageType == MES_PRINCESS) {
		cout << "The princess is on the floor of level " << level << endl;
	}
	return;
}

void messageRoom::SetMessage(int lev) {
	level = lev;
	return;
}