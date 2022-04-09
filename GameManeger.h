#ifndef _GAME_H_
#define _GAME_H_
#define NOTSTARTED 0
#define STARTED 1
#define SCORE 0
#define LIVES 3
#define EXITWITHP 112
#define ESC 27
#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include"Menu.h"
#include "BoardDataBase.h"
using namespace std;
class Game
{
public:
	Game();
	//----------------------------------------RUN AND CONTROL FUNCTIONS----------------------------------------
	void StartGame();
	void run( bool WithColors,int selection, bool& quited,int GhostLevel);
	void InitializeGame(Pacman& player, Ghost* Gharr, int Gharrsize, Board& map, bool WithColors, Fruit& f, int GhostLevel);
	void GhostInitializer(Ghost* Ghostarr, int Gharrsize, Board& map, int GhostLevel);
	void PacmanInitializer(Pacman& player, Board& map);
	void DeleteGhosts(Ghost* Ghostarr, int Gharrsize, Board& map, bool WithColors);
	bool CheckPlayerGhostCollision(Pacman& player, Ghost* Ghostarr, int Gharrsize, Board& map, bool WithColors, int GhostLevel);
	void GhostShellFunctionForMovment(Ghost* Ghostarr, int Gharrsize, Pacman& c, Board& map, bool WithColors);
	void GhostColorInitializer(Ghost* Ghostarr, int Gharrsize, bool WithColor);

private:
	BoardDataBase MapsDatabase;
	Menu M;
	int globalscore=0;

};
#endif
