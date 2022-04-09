#include "Fruit.h"

	int Fruit::GetFruitValue()const
	{//basic get func value
		return (int)this->value;
	}
	bool Fruit::IsFruitOnBoard()const
	{
		return this->onboard;
	}
	//-----------------------------------------------------------

	void Fruit::Set_Fruit_Value(enum value val)
	{//set fruit value
		value = val;
		this->Set_GameObj_Symbol((int)value + INTTOASCII);
	}
	Fruit::Fruit(Color c)
	{//a ctor of fruit using color
		this->Set_GameObj_Color(c);
	}
	void Fruit::Set_Fruit_OnBoard(bool change)
	{//sets the boolean value of the fruit
		this->onboard = change;
	}

	Fruit::~Fruit()
	{

	}
	Fruit::Fruit()
	{

	}


	bool Fruit::FruitFunctionality(Board& b, bool WithColors,Pacman& C, Ghost *Ghostarr,int Gharrsize)
	{        //FRUIT ENTIRE FUNCTIONALITY SHELL FUNC
		static int AppearTime = (rand() % APPERATIMERANGE) + APPERATIMEMOVE;
		static int Moves = 0;
		bool PlayerAteFruit = false;
		if (this->IsFruitOnBoard() == false && AppearTime == Moves)
		{//in this case the fruit is not on board
			AppearTime = (rand() % APPERATIMERANGE) + APPERATIMEMOVE; Moves = 0;
			this->GiveFruitValue();
			this->AppearRandomly(b, WithColors, C, Ghostarr, Gharrsize);
			this->Draw_GameObj(this->GetSym());
		}//fruit needs to appear in a random amount of time
		else if (this->IsFruitOnBoard() == false) Moves++;
		if (this->IsFruitOnBoard() == true) // in this case he is on board , he needs to move slowly until he meets pacman , a ghost , or time runs out
		{
			PlayerAteFruit = FruitBehaviorOnScreen(b, WithColors, C,Ghostarr,Gharrsize);
		}
		return PlayerAteFruit;
	}
	void Fruit::GiveFruitValue()
	{//randomly sets the value of the fruit
		int fruitval = (rand() % FRUITVALUERANGE + FRUITVALNUM);
		if (fruitval == 5) this->Set_Fruit_Value(five);
		if (fruitval == 6) this->Set_Fruit_Value(six);
		if (fruitval == 7) this->Set_Fruit_Value(seven);
		if (fruitval == 8) this->Set_Fruit_Value(eight);
		if (fruitval == 9) this->Set_Fruit_Value(nine);
	}
	//changes the location of the fruit onscreen
	void Fruit::ChangePosAndMakeMove(int x, int y, Board& b, bool WithColors)
		{ //POLYMORPHISM 
		if (!this->CheckLimits(x, y, b))
			{
			this->DeletePrevLocGhostandFriut(b, WithColors);
			this->Set_XandY_Pos(x, y);
			this->Draw_GameObj(this->GetSym());
			}
		}
	//this func randomly chooses the location where the fruit appears
	void Fruit::AppearRandomly(Board& b, bool WithColors, Pacman& C, Ghost* Ghostarr, int Gharrsize)
	{
		int randx, randy;
		while (this->IsFruitOnBoard() == false)
		{
			randx = (rand() % b.GetmapCols()); randy = (rand() % b.GetmapRows());
			if (this->CheckLimits(randx, randy, b) == 0 && randx != C.Get_X_Pos() && randy != C.Get_Y_Pos()
				&& this->FruitAnyGhostHit(randx, randy, Ghostarr, Gharrsize) == 1 && randx < strlen(b.GetRowPointer(randy)))
				if(b.GetSymbol(randx, randy,true) != '%')//if not wall , or not fruit accessible
			{ //drop the fruit if it doesnt touch the  walls , pacman , or the ghosts
				this->Set_XandY_Pos(randx, randy);
				this->Set_Fruit_OnBoard(true);
			}
		}
	}

//this function controls the movement and checks collision with the ghosts / pacman
//also randomly calculates the disappearance time of the fruit
bool Fruit::FruitBehaviorOnScreen(Board& b, bool WithColors, Pacman& C, Ghost* Ghostarr, int Gharrsize)
{
	bool PlayerAteFruit = false;
	static int SomeTime = (rand() % FRUITDISSAPEARRANGE) + FRUITDISSAPEARMOVE;
	static int TimeCounter = 0;
	if (TimeCounter != SomeTime)
	{
		this->Move_Slowly(b, WithColors);
		for (int i = 0; i < Gharrsize; i++)
		{
			if (this->FruitHitAGhost(Ghostarr[i]) == 1) { 
				this->DeleteFruit(b, WithColors); 
				Ghostarr[i].Draw_GameObj(Ghostarr[i].GetSym());
			}
		}//fruit is deleted if it meets a ghost
		if (this->Get_X_Pos() == C.Get_X_Pos() && this->Get_Y_Pos() == C.Get_Y_Pos())
		{
			PlayerAteFruit = true;
			this->DeleteFruit(b, WithColors);
			C.Draw_GameObj(C.GetSym());
		}
		TimeCounter++;
	}
	else
	{
		this->DeleteFruit(b, WithColors);
		SomeTime = (rand() % FRUITDISSAPEARRANGE) + FRUITDISSAPEARMOVE; //next someTime randomizer
		TimeCounter = 0;            //reinitialize timer counter
	}
	return PlayerAteFruit;
}


bool Fruit::FruitAnyGhostHit(int x, int y, Ghost* Ghostarr, int Gharrsize)
{ 
	for (int i = 0; i < Gharrsize; i++)
	{
		if (this->FruitHitAGhost(Ghostarr[i]) == 0)
			return true;
	}
	 return false;
} //this function returns 1 if the fruit doesnt touch ANY GHOST

//controls the movement of the ghost , also moves in a slow order
void Fruit::Move_Slowly(Board& b, bool WithColors)
{
	int x = this->Get_X_Pos(), y = this->Get_Y_Pos(), direction;
	static int MoveCounter = 0;
	if (MoveCounter == SLOWMOVEVAL)
	{
		MoveCounter = 0;
		direction = rand() % 4; // 0 / 1 / 2 / 3
		switch (direction)
		{
		case 0: // Moves right
			x++;
			this->ChangePosAndMakeMove(x, y, b, WithColors);
			break;
		case 1: // Moves left
			x--;
			this->ChangePosAndMakeMove(x, y, b, WithColors);
			break;
		case 2: // Moves up
			y--;
			this->ChangePosAndMakeMove(x, y, b, WithColors);
			break;
		case 3: // Moves down
			y++;
			this->ChangePosAndMakeMove(x, y, b, WithColors);
			break;
		}
	}
	else MoveCounter++;
}

//This function delets the fruit 
void Fruit::DeleteFruit(Board& b, bool WithColors)
{
	this->DeletePrevLocGhostandFriut(b, WithColors);
	this->Set_XandY_Pos(0, 0);
	this->Set_Fruit_OnBoard(false);
}

bool Fruit::FruitHitAGhost(Ghost& AnyGhost)
{ 
	if (this->Get_X_Pos() != AnyGhost.Get_X_Pos()   //if the x is different or the y is differnt its not touching
		|| this->Get_Y_Pos() != AnyGhost.Get_Y_Pos())  //doesnt hit ghost x
		return 0;
	else return 1;
} //this function returns 0 if the fruit doesnt touch A GHOST , return 1 if it is touching!