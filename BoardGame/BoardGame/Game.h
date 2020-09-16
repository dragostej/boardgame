#pragma once
#include "Character.h"
#include "Alpaca.h"
#include "Monster.h"
#include "Position.h"
#include <vector>
#include <set>
#include <time.h>  
#include <algorithm>
#include <chrono>
#include <thread>
#include <iomanip>

class Game
{
private:
	const int tableSize = 8;
	const int numberOfObstacles = 12;
	const std::vector<Position> validSteps = { Position(1, 0), Position(0, -1), Position(-1, 0), Position(0, 1) };
	const std::vector<std::string> validGifts = { "fejdisz", "nyaklanc", "kard" };

	int currentRound;
	int maxRounds;

	bool setMonsterSteps;
	int numberOfMonsterFatRounds;

	/*Statistics*/
	int numberOfAlpacaMeetings;
	int numberOfAlpacaReborn;
	int numberOfMonsterMeal;

	std::vector<Character*> chars;
	std::vector<Position> obstacles;
	std::vector<Gift*> gifts;

	void InitGame();
	std::vector<Position> DrawDifferentPositions(int numberOfPositions, int numberOfAlpacas, int numberOfMonsters, int numberOfObstacles);
	void drawGifts(int numberOfGifts);
	char GetPositionType(int i, int j);
	Position GetNewPosition();
	bool CollisionDetect(int currentPlayer);
	void HandleCollision(Character* currentPlayer, Character* otherPlayer);

public:
	Game();
	Game(int NumberOfRounds);
	~Game();
	void Draw();
	void ExecuteRound();
	void RunGame();
	void ShowStatistics();

};

