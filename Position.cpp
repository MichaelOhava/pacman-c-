//מיקום של אובייקט כלשהו במסך, תכיל כנראה פונקציה לתזוזה במסך
#include"Position.h"

int Position::Get_X_Pos() const
 {
	 return X_Pos;
 }
int Position::Get_Y_Pos() const
{
	return Y_Pos;
}
void Position::Set_XandY_Pos(int x, int y) {
	this->X_Pos = x;
	this->Y_Pos = y;
}
Position::~Position()
{

}