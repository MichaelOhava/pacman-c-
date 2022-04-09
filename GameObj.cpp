#include "GameObj.h"

//This function gets pacman color
Color GameObj::GetColor()const
{
	return this->color;
}

//This function gets pacman symbol
char GameObj::GetSym()const
{
	return this->symbol;
}

//------------------------------------------------------------------------------------
//This function sets pacman color
void GameObj::Set_GameObj_Color(Color c)
{
	color = c;
}

//This function sets pacman symbol
void GameObj::Set_GameObj_Symbol(char Sym)
{
	this->symbol = Sym;
}

//This function draws onject symbol
void GameObj::Draw_GameObj(char ch)const
{
	setTextColor(color);
	gotoxy(this->Get_X_Pos(), this->Get_Y_Pos());
	cout << this->symbol << endl;
}

//This function checks if wall is ahead
int  GameObj::CheckIfWall(int x, int y, Board& b)
{
	if (b.GetSymbol(x, y,false) == '#' || b.GetSymbol(x, y,false) == '-')
		return 1;
	return 0;
}

//This funcion delets ghosts or fruits prev location
void GameObj::DeletePrevLocGhostandFriut(Board& b, bool WithColors)const
{
	if (WithColors)
		setTextColor(Color::LIGHTRED);
	gotoxy(this->Get_X_Pos(), this->Get_Y_Pos());
	cout << b.GetSymbol(this->Get_X_Pos(), this->Get_Y_Pos(),false);
}

//This funcion delets pacmans prev location
void GameObj::DeletePrevLoc()const
{
	gotoxy(this->Get_X_Pos(), this->Get_Y_Pos());
	setTextColor(Color::WHITE);
	cout << " ";
}

//This function make an object movement
void GameObj::ChangePosAndMakeMove(int x, int y, Board& b, bool WithColors)
{
	DeletePrevLoc();
	Set_XandY_Pos(x,y);
	Draw_GameObj(this->GetSym());
}

//This function checks limit acorrding to heir 
int GameObj::CheckLimits(int x, int y, Board& b)
{ 
	if (y + 1 > b.GetmapRows()/*down*/ || y - 1 < 0 /*up*/ || x + 1 > b.GetmapCols()/*right*/ || x - 1 < 0/*left*/|| b.GetSymbol(x, y,false) == '#')
		return 1;
	/*else if (b.GetSymbol(x, y) == '#')
		return 1;*/
	return 0;
		
}