// BoardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Position.h"
#include "Character.h"
#include "Alpaca.h"
#include "Game.h"


int main(int argc, char *argv[])
{
	srand(time(NULL));

	Game g(atoi(argv[1]));
	g.RunGame();

}
