#ifndef _PACMAN_H
#define _PACMAN_H
#pragma once
#include "GameObj.h"

class Pacman : public GameObj
{
public:
	Pacman(int x, int y, char c);
	~Pacman();
	Pacman();
	//------------------------------------------------------------------------------------
	void UpdateScore(int x, int y, Board& b, bool WithColors, bool PlayerAteFruit, int val);
	void Pacman_movment(char direction, Pacman& p, Board& b, bool WithColors) const;
	int IsTunnelAhead(int x, int y, Board& b, char dir);
	void MovePlayer(int x, int y, Board& b, Pacman& p, char direction, bool WithColors);
	int ValidKeys(char input);

private:
};
#endif // !_PACMAN_
