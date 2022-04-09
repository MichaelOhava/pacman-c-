#include "Menu.h"

// This funcion navigate the user in the maps database
int Menu::MapSelectionMenu(BoardDataBase &Db)const
{
	char choice;
	int out;
	MapSelectionMenuprinter(Db.GetDB_Size(),Db);
	std::cin >> choice;
	while ((choice- CONVERTCHARTOINT) > Db.GetDB_Size() || (choice- CONVERTCHARTOINT) <= 0  /*!isdigit(choice)*/) {
		while (getchar() != '\n') {}

		MapSelectionMenuprinter(Db.GetDB_Size(), Db);
		std::cout << "Please enter number between 1 to "<< Db.GetDB_Size()<<"!" << endl;
		std::cin >> choice;
	}
	clear_screen();
	out = choice - CONVERTCHARTOINT-1;
	return out;
}

// This funcion asks the user for ghost level he wants to play
int Menu::SelectGhostLevel()const {
	char level; 
	cout << "Please choose ghost level:" << endl;
	cout << "1.Hard" << endl << "2.Normal" << endl << "3.Easy" << endl;
	std::cin >> level;
	while ((level - CONVERTCHARTOINT) > 3 || (level - CONVERTCHARTOINT) <= 0) {
		while (getchar() != '\n') {}
		std::cout << "Please enter number between 1 to 3 !" << endl;
		std::cin >> level;
	}
	clear_screen();
		return (level - CONVERTCHARTOINT - 1);
}

// This funcion print the maps names
void Menu::MapSelectionMenuprinter(int dbsize , BoardDataBase& Db)const {
	
	
	clear_screen();
	for (int i = 0; i < dbsize; i++) 
		std::cout << "(" << i + 1 << ") Press " << i + 1 << " to Start a new game with map " << Db.getRawFileName(i) << endl;
}

// This funcion asks the user if he wants to play with colors
int Menu::PlayWithColors(){
	char choice;
	clear_screen();
	std::cout << "Please type 1 to play with colors and type 0 to play without colors" << endl;
	std::cin >> choice;
	while ((choice - CONVERTCHARTOINT) != 0 && (choice - CONVERTCHARTOINT) != 1) {
		while (getchar() != '\n') {}
		std::cout << "Please enter number enter 0 or 1!!" << endl;
		std::cin >> choice;
	}
	clear_screen();
	return (choice - CONVERTCHARTOINT);
}

//This funcion prints the menu of the game
void Menu::ShowMenu(int From)const {
	hideCursor();
	setTextColor(Color::WHITE);

	if (From == MENU)
	{
		cout << "(1) Start a new game by defult levels" << endl;
		cout << "(2) Start a new game by selecting map " << endl;
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl;
	}
	else {
		cout << "(1) Start a new game" << endl;
		cout << "(9) EXIT" << endl;
	}
}

//This funcion prints the instructions of the game--להעביר למחלקת MAIN
char Menu::instrucions() const
{
	char x;
	clear_screen();
	cout << "------WELCOME TO THE PACMAN GAME ! ------" << endl;
	cout << " ------- The keys: ------" << endl;
	cout << "LEFT  |a| or |A|" << endl;
	cout << "RIGHT |d| or |D|" << endl;
	cout << "UP    |w| or |W|" << endl;
	cout << "Down  |x| or |X|" << endl;
	cout << "STAY  |s| or |S|" << endl;
	cout << " ------ How To Play: -------" << endl;
	cout << "Use the keys listed above to collect all the points (.)" << endl;
	cout << "Avoid the Ghosts! If a ghost catches you you lose 1 life" << endl;
	cout << "You have 3 lives at the start of each game" << endl;
	cout << "If you lose all 3 lives then GAME OVER" << endl;
	cout << "If you manage to collect all the points (.) without dying YOU WIN!" << endl;
	cout << " ------ ENJOY -------" << endl;
	cout << "enter 1 or 2 To Play , 9 To Exit" << endl;
	cin >> x;
	return x;
}

//This funcion checks if the input inserted in the menu is legal
void Menu::CheckValidOption(char& x, int From) 
{
	clear_screen();
	cout << "invalid option!" << endl;
	if (From == MENU)
		ShowMenu(MENU);
	else ShowMenu(INSTRUCTIONS);
	getchar();
	cin >> x;

	/*-------*/
	if (From == MENU)
	{
		while (!(x == '1' || x == '9' || x == '8')) {
			clear_screen();
			cout << "invalid option!" << endl;
			ShowMenu(MENU);
			getchar();
			cin >> x;
		}
	}
	else while (!(x == '1' || x == '9')) {
		clear_screen();
		cout << "invalid option!" << endl;
		ShowMenu(INSTRUCTIONS);
		getchar();
		cin >> x;
	}
}

//This funciont checks why the game ended , and prints massage acorrding to the reason 
int Menu::CheckWhyEndGame(char key, int score,int scoretowin,int lives)const
{
	setTextColor(Color::WHITE);
	clear_screen();
	if ( lives== 0)
		cout << "You have lost all of your lives, GAME OVER!\n";
	else if (score >= scoretowin) {
		cout << "You have won the level!\n";
		return WONLEVEL;
	}
	else//(key == EXITWITHP)
		cout << "Thanks for playing!\n";
	cout << "Press any key to coninue..." << endl;
	Sleep(800);
	while (!_kbhit());
	_flushall();
	return QUITGAME;
}

//This funcion alart the player when he hits a ghost
void Menu::GhostHitNotification(int LiveYCord, int LiveXCord)
{
	setTextColor(Color::WHITE);
	gotoxy((LiveYCord - Ycordcorrection), (LiveXCord + Xcordcorrection));
	cout << "YOU HIT A GHOST!" << endl;
	Sleep(800);
	gotoxy((LiveYCord - Ycordcorrection), (LiveXCord + Xcordcorrection));
	cout << "                " << endl;
}

//This funcion pauses/unpauses the game if user ask for 
void Menu::PauseUnPauseFunc(char& key, char keyreminder, int LiveYCord, int LiveXCord)
{
	setTextColor(Color::WHITE);
	gotoxy((LiveYCord - Ycordcorrection), (LiveXCord + Xcordcorrection));
	gotoxy((LiveYCord - Ycordcorrection), (LiveXCord + Xcordcorrection));
	cout << "PAUSED,ESC TO PLAY" << endl;
	do
	{
		_kbhit();
		key = _getch();
	} while (key != ESC);
	key = keyreminder;//resume game
	gotoxy((LiveYCord - Ycordcorrection), (LiveXCord + Xcordcorrection));
	cout << "                   ";
}

//This funcion prints winning message 
void Menu::ChampMessage() {
	clear_screen();
	cout << "You have won the game!!!"<<endl;
	Sleep(1500);
}

//This funcion prints moving level message
void Menu::MovingLevel() {
	cout << "Press any key to continue to the next level "<<endl;
	while (!_kbhit());
	clear_screen();
}