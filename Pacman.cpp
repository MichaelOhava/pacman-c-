#include "Pacman.h"

//This function is a constructor
Pacman::Pacman(int x, int y, char c)
{
	this->Set_XandY_Pos(x, y);
	this->Set_GameObj_Symbol(c);
}
//This function is a destructor
Pacman::~Pacman()
{

}

Pacman::Pacman() {};

//------------------------------------------------------------------------------------

//This funcion manage the pacman movement
void Pacman::Pacman_movment(char direction, Pacman& p, Board& b, bool WithColors) const
{
	
	char input = 0;
	int x = this->Get_X_Pos();
	int y = this->Get_Y_Pos();
	direction = tolower(direction);
	switch (direction)
	{
	case 'd':
		if (!p.IsTunnelAhead(x, y, b,direction))
			x++;
		else x = 0;
		p.MovePlayer(x, y, b, p, direction, WithColors);
		break;
	case 'a':
		if (!p.IsTunnelAhead(x, y, b, direction))
			x--;
		else x = b.GetmapCols()-1;
		p.MovePlayer(x, y, b, p, direction, WithColors);
		break;
	case 'w':
		if (!p.IsTunnelAhead(x, y, b, direction))
			y--;
		else y = b.GetmapRows()-1;
		p.MovePlayer(x, y, b, p, direction, WithColors);
		break;
	case 'x':
		if (!p.IsTunnelAhead(x, y, b, direction))
			y++;
		else y = 0;
		p.MovePlayer(x, y, b, p,direction, WithColors);
		break;
	case 's'://s = stop
		break;
	default:
		//KEEP MOVING SAME DIRECTION
		break;
	}
}

//This function checks if there is a tunnel ahead
int Pacman::IsTunnelAhead(int x,int y, Board& b,char dir)
{
	if (y+1==b.GetmapRows()&&dir=='x'/*down*/ || y == 0&&dir == 'w'/*up*/ || x + 1 == b.GetmapCols()&& dir == 'd'/*right*/ || x == 0&& dir == 'a'/*left*/)
		return 1;
	else return 0;
}

//This funcion responsible update 
void Pacman::UpdateScore(int x, int y, Board&  b, bool WithColors, bool PlayerAteFruit, int val)
{
		if (b.GetSymbol(x, y,false) == '.' && PlayerAteFruit == false)
		{
			b.SetArrCell(x, y);
			b.SetScore(WithColors, 0);
		}
		else if (PlayerAteFruit == true)
		{
			b.SetArrCell(x, y);
			b.SetScore(WithColors, val);
		}
}

//This funcion strats the movment process acorrding to Pacman_movment function inputs
void Pacman::MovePlayer(int x,int y,Board& b,Pacman& p,char direction ,bool WithColors)
{
	int TunnelExit, additionx = 0, additiony = 0;;
	if (!p.CheckIfWall(x, y, b))
	{
		/*if (!p.IsTunnelAhead(x, y, b)){*/
			this->ChangePosAndMakeMove(x, y,b,WithColors);
			p.UpdateScore(x, y, b, WithColors, false, 0);
		/*}*/
		/*else
		{
			switch (TunnelExit)
			{
			case 0:additionx = 1;break;
			case 1:additionx = -1; break;
			case 2:additiony = 1; break;
			default:additiony = -1;break;
			}
			this->ChangePosAndMakeMove(b.GetTunneXlLoc(TunnelExit)+additionx, b.GetTunneYlLoc(TunnelExit)+additiony,b,WithColors);
			p.UpdateScore(x, y, b, WithColors, false, 0);
		}*/
	}
}

//This funcion checks if the user hits legal input
int Pacman::ValidKeys(char input)
{
	if (input == 'a' || input == 'd' || input == 'w' || input == 'x' || input == 's')
		return 1;
	else if (input == 'A' || input == 'D' || input == 'W' || input == 'X' || input == 'S')
		return 1;
	return 0;
}



