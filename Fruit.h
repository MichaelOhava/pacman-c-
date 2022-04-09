#ifndef _FRUIT_H
#define _FRUIT_H
#pragma once
#include "Pacman.h"
#include "Ghost.h"
#include "GameObj.h"
#define INTTOASCII 48
#define APPERATIMERANGE 8
#define FRUITVALUERANGE 5
#define FRUITVALNUM 5
#define APPERATIMEMOVE 25
#define SLOWMOVEVAL 9
#define FRUITDISSAPEARRANGE 4
#define FRUITDISSAPEARMOVE 60
//possible fruit value range:
enum value { five = 5, six = 6, seven = 7, eight = 8, nine = 9 };

class Fruit : public GameObj
{
private:
	value value;
	bool onboard = false; //tells if Fruit is currently on board or off board
public:
	int GetFruitValue()const;
	bool IsFruitOnBoard()const;
	//-----------------------------------------------------------
	void Set_Fruit_Value(enum value val);
	void Set_Fruit_OnBoard(bool change);
	Fruit(Color c);
	~Fruit();
	Fruit();
	//-----------------------------------------------------------
	bool FruitFunctionality(Board& b, bool WithColors, Pacman& C, Ghost* Ghostarr, int Gharrsize);
	void ChangePosAndMakeMove(int x, int y, Board& b, bool WithColors);//POLYMORPHISM
	//-----------------------------------------------------------
	void AppearRandomly(Board& b, bool WithColors, Pacman& C, Ghost* Ghostarr, int Gharrsize);
	bool FruitBehaviorOnScreen(Board& b, bool WithColors, Pacman& C, Ghost* Ghostarr, int Gharrsize);
	bool FruitAnyGhostHit(int x, int y, Ghost* Ghostarr, int Gharrsize);
	void Move_Slowly(Board& b, bool WithColors);
	void DeleteFruit(Board& b, bool WithColors);
	bool FruitHitAGhost(Ghost& AnyGhost);
	void GiveFruitValue();
};

#endif