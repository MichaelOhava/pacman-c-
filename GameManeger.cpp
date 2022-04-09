#include "GameManeger.h"

//----------------------------------------RUN FUNCTIONS----------------------------------------

//This funcion navigates the player throw the game
void Game::StartGame() {
	char x = 0;
	int i, j, selection = 0, GhostLevel = 0;
	bool WithColors = false,quited;
	if (!MapsDatabase.FindFilesInDictionary()) {;
		return;}
	for (i = 0; i < MapsDatabase.GetDB_Size(); i++)
		MapsDatabase.get_Database()[i].map.SetLocationsForMap();
	while (x != '9')
	{
		quited = false;
		clear_screen();
		M.ShowMenu(MENU);
		std::cin >> x;
		if (!(x == '1' || x=='2' || x == '9' || x == '8'))
			M.CheckValidOption(x, MENU);
		if (x == '1') {
			if (M.PlayWithColors())
				WithColors = true;
			GhostLevel = M.SelectGhostLevel();
			for (j = 0; j < MapsDatabase.GetDB_Size(); j++)
			{
				this->run(WithColors,j,quited,GhostLevel);
				if (quited) j = MapsDatabase.GetDB_Size();
				else M.MovingLevel();
			}
			if (!quited)M.ChampMessage();
		}
		else if (x == '2') {//play with map selectoin menu
			if (M.PlayWithColors())
				WithColors = true;
			GhostLevel = M.SelectGhostLevel();
			selection = M.MapSelectionMenu( MapsDatabase );
			this->run(WithColors, selection,quited, GhostLevel);
		}
		else if (x == '8')
			x=M.instrucions();
		else { 
			std::cout << "Goodbye !" << endl; exit(1);
		}
		WithColors = false;
		globalscore = 0;
	}
	MapsDatabase.FreeMapsArr();
}
 
//This funcion runs the game
void Game::run(bool WithColors,int Selection,bool &quited,int GhostLevel)
{
	Board b = MapsDatabase.get_Database()[Selection].map;
	int GameBegun = 0,whyend,Gharrsize=b.GetGhostArrSize();
	bool AteFruit = false;
	char key = 't',keyhelper=0,speedmode=0;
	Pacman c; Ghost Ghostarr[4]; Fruit F(Color::WHITE);
	InitializeGame(c, Ghostarr, Gharrsize, b ,WithColors,F,GhostLevel);
	do {// p(Ascii 112) ends the loop
		hideCursor();
		if (CheckPlayerGhostCollision(c, Ghostarr, Gharrsize,b,WithColors, GhostLevel))
		key = 's';
		if (_kbhit())
			key = _getch();
		if (key == ESC)//esc was pressed 
			M.PauseUnPauseFunc(key, keyhelper, b.GetLiveYCord(), b.GetLiveXCord());
		if (c.ValidKeys(key))
		{
			GameBegun = STARTED;
			if (key != ESC) { keyhelper = key; }
			c.Pacman_movment(key, c, b,WithColors);
		}
		else if (key != 's' && tolower(key) != EXITWITHP) //KEEP MOVING
			c.Pacman_movment(keyhelper, c, b ,WithColors);
		//---------------FRUIT IMPLEMENTATION---------------
		if(GameBegun != NOTSTARTED)
		AteFruit = F.FruitFunctionality(b, WithColors, c, Ghostarr, Gharrsize);
		if (AteFruit == true)
			c.UpdateScore(c.Get_X_Pos(), c.Get_Y_Pos(),b, WithColors, AteFruit, F.GetFruitValue());
		//---------------Ghosts---------------
		++speedmode;
		if (key != ESC && GameBegun != NOTSTARTED && speedmode % 2 == 0) {
			GhostShellFunctionForMovment(Ghostarr, Gharrsize, c, b,WithColors);
		}
		Sleep(200);
	} while (tolower(key) != EXITWITHP && (b.GetScore()-globalscore) < b.GetScoreToWin()&& b.GetLives()!= 0);
		whyend = M.CheckWhyEndGame(key, b.GetScore(), b.GetScoreToWin(), b.GetLives());
		if(whyend==WONLEVEL)globalscore += b.GetScore();
		if (whyend == QUITGAME)quited = true;
	
}

//This funcion is a defult constractor
Game::Game()
{

}

//This funcioninitilaizing objects location and colors if demanded
void Game::InitializeGame(Pacman& player, Ghost *Gharr,int Gharrsize, Board& map, bool WithColors,Fruit& f,int GhostLevel)
{
	if (WithColors) {
		f.Set_GameObj_Color(Color::LIGHTGREEN);
		player.Set_GameObj_Color(Color::YELLOW);
		GhostColorInitializer(Gharr, Gharrsize, WithColors);
	}
	else {
		f.Set_GameObj_Color(Color::WHITE);
		player.Set_GameObj_Color(Color::WHITE);
		GhostColorInitializer(Gharr, Gharrsize, WithColors);
	}
	clear_screen();
	map.Creatcpy();
	map.SetScoreWithGlobal(globalscore);
	map.Printmap(WithColors);
	PacmanInitializer(player, map);
	GhostInitializer(Gharr,Gharrsize, map, GhostLevel);

}

//This funcion check id ghost hit pacman, if so pacman goes back to start(also ghosts) and loses life
bool Game::CheckPlayerGhostCollision(Pacman& player, Ghost* Ghostarr, int Gharrsize,Board& map,bool WithColors, int GhostLevel)
{
	for (int i = 0; i < Gharrsize; i++) {
		if (player.Get_X_Pos() == Ghostarr[i].Get_X_Pos() && player.Get_Y_Pos() == Ghostarr[i].Get_Y_Pos())
		{
			M.GhostHitNotification(map.GetLiveYCord(), map.GetLiveXCord());
			DeleteGhosts(Ghostarr,Gharrsize,map, WithColors);
			player.DeletePrevLoc();
			map.SetLife(WithColors);
			PacmanInitializer(player, map);
			GhostInitializer(Ghostarr, Gharrsize, map, GhostLevel);
			return true;
		}
	}
	return false;
}

//This function sets the pacman initial location on current map
void Game::PacmanInitializer(Pacman& player, Board& map) //זה הפאקמן  ואחריו זה הגוסט - להפוך לגנרי בהורשה
{
	player.Set_XandY_Pos(map.GetPacmanXCords(), map.GetPacmanYCords());
	player.Set_GameObj_Symbol('C');
	player.Draw_GameObj(player.GetSym());
} 

//This function sets the ghosts initial location on current map
void Game::GhostInitializer(Ghost*Ghostarr, int Gharrsize, Board& map,int GhostLevel) 
{
	for (int i = 0; i < Gharrsize; i++) {
		Ghostarr[i].Set_XandY_Pos(map.GetGhostYCords(i), map.GetGhostXCords(i));
		Ghostarr[i].Set_GameObj_Symbol(234);
		Ghostarr[i].Draw_GameObj(Ghostarr[i].GetSym());
		switch (GhostLevel)
		{
		case 0:
			Ghostarr[i].Set_Ghost_Intellegence(Best);
			break;
		case 1:
			Ghostarr[i].Set_Ghost_Intellegence(Good);
			break;
		default://2
			Ghostarr[i].Set_Ghost_Intellegence(Novice);
			break;
		}
	}
}

//This function initial the ghosts colors
void Game::GhostColorInitializer(Ghost*Ghostarr, int Gharrsize, bool WithColor) {
	for (int i = 0; i < Gharrsize; i++) {
		if (WithColor) {
			switch (i)
			{
			case 0:
				Ghostarr[i].Set_GameObj_Color(Color::BROWN);
				break;
			case 1:
				Ghostarr[i].Set_GameObj_Color(Color::CYAN);
				break;
			case 2:
				Ghostarr[i].Set_GameObj_Color(Color::WHITE);
				break;
			case 3:
				Ghostarr[i].Set_GameObj_Color(Color::LIGHTMAGENTA);
				break;
			default:
				break;
			}
		}
		else Ghostarr[i].Set_GameObj_Color(Color::WHITE);
	}
}

//This function deletes the ghosts from thier locations on current map
void Game::DeleteGhosts(Ghost*Ghostarr, int Gharrsize, Board& map,bool WithColors)
{
	for (int i = 0; i < Gharrsize; i++)
	Ghostarr[i].DeletePrevLocGhostandFriut(map, WithColors);
}

//This function responsible for the ghost movment
void Game::GhostShellFunctionForMovment(Ghost*Ghostarr, int Gharrsize, Pacman& c, Board& map, bool WithColors) {
	for (int i = 0; i < Gharrsize; i++)
		Ghostarr[i].GhostMove(map, WithColors, c);
}
