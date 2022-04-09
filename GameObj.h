#pragma once
#include "Position.h"
#include "Colors.h"
#include "Board.h"

class GameObj : public Position
{
private:
	char symbol;
	Color color;
public:
	Color GetColor()const;
	char GetSym()const;
	//------------------------------------------------------------------------------------
	void Set_GameObj_Color(Color c);
	void Set_GameObj_Symbol(char Sym);
	//----------these functions can be hereditery:---------------------------------------
	void Draw_GameObj(char ch)const;
	int  CheckIfWall(int x, int y, Board& b);
    void DeletePrevLoc()const;
	void DeletePrevLocGhostandFriut(Board& b, bool WithColors)const;
	virtual void ChangePosAndMakeMove(int x, int y, Board& b, bool WithColors);
	virtual int CheckLimits(int x, int y, Board& b);
};

