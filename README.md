# pacman-c++-OOP 
NOTE:this was implemented in Visual Studio 2019, using C++ 14

# NOTES:
#This game was implemented using OOP concepts. <br />
#Ghost chase hard and normal algorithms were implemented using BFS algorithm. <br />
#Screens can be created by the user! <br />
#Can be played In-Color mode, or in Basic black and white mode. <br />
#Upon crossing the wall limits of the screen, pacman teleports to the other side. <br />
<br />
# HOW TO CREATE YOUR OWN MAP:
This program can be played on screens the user creates! meaning using a text file in the following format
they can be loaded into the game and played upon
the rules are: <br />
The screen file should be a text file representing the screen, with: <br />
'@' - for the position of the pacman (1 and only) <br />
'$' - for the initial position of the ghosts (allow any number between 0 to 4) <br />
'#' - for walls <br />
'%' - for “empty” positions that should not have a breadcrumb <br />
'&' - for the position where the points and remaining lives information (“legend”) shall be presented <br />

The game comes with 3 pre-loaded maps! you can use them for refrence to check out how *.screen files should be created
for usage in the game.

# PACMAN CONTROLS
pacman control scheme: <br />
Keys: <br />
LEFT :a or A <br />
RIGHT : d or D <br />
UP : w or W <br />
Down : x or X <br />
STAY : s or S <br />

