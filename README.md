# pacman-c++-OOP 
NOTE:this was implemented in Visual Studio 2019, using C++ 14

#This game was implemented using OOP concepts.
#Ghost chase hard and normal algorithms were implemented using BFS algorithm.
#Screens can be created by the user!
#Can be played In-Color mode, or in Basic black and white mode.
#Upon crossing the wall limits of the screen, pacman teleports to the other side.

This program can be played on screens the user creates! meaning using a text file in the following format
they can be loaded into the game and played upon
the rules are:
The screen file should be a text file representing the screen, with:
@ - for the position of the pacman (1 and only)
$ - for the initial position of the ghosts (allow any number between 0 to 4)
'#' - for walls
% - for “empty” positions that should not have a breadcrumb
& - for the position where the points and remaining lives information (“legend”) shall be presented

The game comes with 3 pre-loaded maps! you can use them for refrence to check out how *.screen files should be created
for usage in the game.

pacman control scheme:
Keys:
LEFT
a or A
RIGHT
d or D
UP
w or W
Down
x or X
STAY
s or S

