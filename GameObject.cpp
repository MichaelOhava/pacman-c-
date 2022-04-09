//מחלקה כללית לתיאור אובייקטים במשחק , תכיל את מיקום האובייקט במסך, באמצעות המחלקה
#include "GameObject.h"

GameObj::~GameObj()
{
}

void GameObj::Draw_Obj(char ch)const
{
	cout << ch << endl;
}

void GameObj::Set_Positiot_cor(int x, int y)
{
	this->Pos.Set_XandY_Pos(x, y);
}
void GameObj::DeletePrevLoc(GameObj& Object)const
{
	gotoxy(Object.Pos.Get_X_Pos(), Object.Pos.Get_X_Pos());
	cout << " ";
}

void GameObj::Object_movment(char direction, GameObj& Object) const
{
	int x = Object.Pos.Get_X_Pos();
	int y = Object.Pos.Get_Y_Pos();
	 direction=tolower(direction);
	switch (direction)
	{
	case 'd':
		//validation from board that its not a wall/tannel
		SetObjPosAndMakeMove(++x,y,Object);
		break;
	case 'a':
		//validation from board that its not a wall/tannel
		SetObjPosAndMakeMove(--x, y, Object);
		break;
	case 'w':
		//validation from board that its not a wall/tannel
		SetObjPosAndMakeMove(x, ++y, Object);
		break;
	case 'x':
		//validation from board that its not a wall/tannel
		SetObjPosAndMakeMove(x, --y, Object);
		break;
	default://s

		break;
	}
}
void GameObj::SetObjPosAndMakeMove(int x, int y, GameObj& Object)const
{

	Object.DeletePrevLoc(Object);
	Object.Set_Positiot_cor(x, y);
	gotoxy(x, y);
	Object.Draw_Obj(Object.Symbol);
}