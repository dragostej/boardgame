#include "pch.h"
#include "Game.h"



void Game::InitGame()
{
	std::vector<Position> drawedPositions;
	drawedPositions = DrawDifferentPositions( 3 + numberOfObstacles, 2, 1, numberOfObstacles);
	drawGifts(2);

	chars.push_back(new Alpaca(drawedPositions[0], gifts[0]));
	chars.push_back(new Alpaca(drawedPositions[1], gifts[1]));
	chars.push_back(new Monster(drawedPositions[2]));

	for (int i = 3; i < 3 + numberOfObstacles; i++)
	{
		obstacles.push_back(drawedPositions[i]);
	}

	std::cout << "Kezdo felallas: " << std::endl;

	std::cout << "Alpaka1 ajandek targya: ";
	dynamic_cast<Alpaca*>(chars[0])->ShowGift();

	std::cout << "Alpaka2 ajandek targya: ";
	dynamic_cast<Alpaca*>(chars[1])->ShowGift();

	Draw();

}

std::vector<Position> Game::DrawDifferentPositions(int numberOfPositions, int numberOfAlpacas, int numberOfMonsters, int numberOfObstacles)
{
	std::vector<Position> positions;

	int x, y;

	do
	{
		x = rand() % tableSize + 1;
		y = rand() % tableSize + 1;

		Position p(x, y);

		if (std::find(positions.begin(), positions.end(), p) == positions.end())
			positions.push_back(p);

	} while (positions.size()!=numberOfPositions);

	for (int i = 0; i < numberOfAlpacas; i++)
		positions[i].SetType('a');

	for (int i = numberOfAlpacas; i < numberOfAlpacas + numberOfMonsters; i++)
		positions[i].SetType('m');

	for (int i = numberOfAlpacas + numberOfMonsters; i < numberOfAlpacas + numberOfMonsters + numberOfObstacles; i++)
		positions[i].SetType('X');

	return positions;
}

void Game::drawGifts(int numberOfGifts)
{
	for (int i = 0; i < numberOfGifts; i++)
	{
		int random = rand() % validGifts.size();
		gifts.push_back(new Gift(validGifts[random]));
	}

}

char Game::GetPositionType(int i, int j)
{
	char r = '.';

	for (size_t k = 0; k < this->chars.size(); k++)
	{
		if (chars[k]->GetPosition() == Position(i, j))
		{
			r = chars[k]->GetPosition().GetType();
			return r;
		}
	}

	
	for (size_t k = 0; k < this->obstacles.size(); k++)
	{
		if (obstacles[k] == Position(i, j))
		{
			r = obstacles[k].GetType();
			return r;
		}
	}
	return r;
}

Position Game::GetNewPosition()
{
	int x, y;
	bool similarCharPosition = false;
	bool similarObstaclePosition = false;
	Position p;

	for (;;)
	{
		similarCharPosition = false;
		similarObstaclePosition = false;

		x = rand() % tableSize + 1;
		y = rand() % tableSize + 1;

		p.SetX(x);
		p.SetY(y);

		for (size_t i = 0; i < chars.size(); i++)
		{
			if (chars[i]->GetPosition() == p) 
			{
				similarCharPosition = true;
				break;
			}
		}

		for (size_t i = 0; i < obstacles.size(); i++)
		{
			if (obstacles[i] == p) 
			{
				similarObstaclePosition = true;
				break;
			}
		}

		if (similarCharPosition == false && similarObstaclePosition == false)
			break;

	}

	return p;
}

Game::Game()
{
}

Game::Game(int NumberOfRounds)
{
	this->maxRounds = NumberOfRounds;
	setMonsterSteps = false;

	numberOfMonsterFatRounds = 0;
	numberOfAlpacaMeetings = 0;
	numberOfAlpacaReborn = 0;
	numberOfMonsterMeal = 0;
	
	InitGame();
}


Game::~Game()
{
	for (size_t i = 0; i < chars.size(); i++)
		delete chars[i];

	for (size_t i = 0; i < gifts.size(); i++)
		delete gifts[i];
}

void Game::Draw()
{
	std::cout << std::endl;
	for (int i = 1; i <= this->tableSize; i++)
	{
		for (int j = 1; j <= this->tableSize; j++)
		{
			std::cout << this->GetPositionType(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

void Game::ExecuteRound()
{
	auto start = std::chrono::high_resolution_clock::now();

	numberOfMonsterFatRounds--;
	
	if (numberOfMonsterFatRounds < 0)
	{
		chars[2]->SetAllowedSteps(3);
		numberOfMonsterFatRounds = 0;

		std::cout << "Az alpaka evo szorny teljes sebesseggel robog." << std::endl;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Az alpaka evo szorny meghizva kozlekedik." << std::endl;
		std::cout << std::endl;
	}

	for (size_t i = 0; i < chars.size(); i++)
	{
		int allowedSteps = chars[i]->GetAllowedSteps();
		for (int j = 0; j < allowedSteps; j++)
		{
			chars[i]->Move(validSteps, tableSize, obstacles, i);
			CollisionDetect(i);
			//Draw();
		}
	}

	if (setMonsterSteps)
	{
		chars[2]->SetAllowedSteps(1);
		numberOfMonsterFatRounds = 5;
		setMonsterSteps = false;
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	
	Draw();
}

void Game::RunGame()
{
	for (int i = 0; i < this->maxRounds; i++)
	{
		std::cout << std::endl;
		std::cout << i+1 << ". KOR:" << std::endl;
		std::cout << std::endl;
		this->ExecuteRound();

		if ((i + 1) % 20 == 0)
			ShowStatistics();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	ShowStatistics();
}

void Game::ShowStatistics()
{
	int colWidth = 30;
	
	std::cout << std::endl;
	std::cout << std::setfill('*') << std::setw(3 * colWidth) << "*" << std::endl;
	std::cout << std::setfill(' ') << std::fixed;
	std::cout << std::setw(colWidth) << "Alpaka talalkozasok" << std::setw(colWidth) << "Alpaka ujjaszuletesek" << std::setw(colWidth) << "Alpaka evo szorny etkezesek" << std::endl;
	std::cout << std::setfill('*') << std::setw(3 * colWidth) << "*" << std::endl;
	std::cout << std::setfill(' ') << std::fixed;
	
	std::cout  << std::setw(colWidth) << numberOfAlpacaMeetings << std::setw(colWidth) << numberOfAlpacaReborn << std::setw(colWidth) << numberOfMonsterMeal << std::endl;

	std::cout << std::endl;
}

bool Game::CollisionDetect(int currentPlayer)
{
	for (size_t i = 0; i < chars.size(); i++)
	{
		if (chars[i]->GetPosition() == chars[currentPlayer]->GetPosition() && i != currentPlayer)
		{
			HandleCollision(chars[currentPlayer], chars[i]);
			
			return true;
		}	
	}
	return false;
}

void Game::HandleCollision(Character* currentPlayer, Character* otherPlayer)
{
	if (dynamic_cast<Alpaca*>(currentPlayer) && dynamic_cast<Alpaca*>(otherPlayer))
	{
		Alpaca* a1 = dynamic_cast<Alpaca*>(currentPlayer);
		Alpaca* a2 = dynamic_cast<Alpaca*>(otherPlayer);

		std::cout << std::endl;
		std::cout << "Az alpakak udvozlik egymast es ajandekot cserelnek." << std::endl;
		std::cout << std::endl;

		a1->Welcome(1);
		a2->Welcome(2);

		a1->ChangeGift(a2);
		numberOfAlpacaMeetings++;

		std::cout << std::endl;
		std::cout << "Alpaka1 ajandek targya: ";
		a1->ShowGift();

		std::cout << "Alpaka2 ajandek targya: ";
		a2->ShowGift();
		std::cout << std::endl;

	}
	else if (dynamic_cast<Monster*>(currentPlayer) && dynamic_cast<Alpaca*>(otherPlayer))
	{

		Monster* m = dynamic_cast<Monster*>(currentPlayer);
		Alpaca* a = dynamic_cast<Alpaca*>(otherPlayer);

		std::cout << std::endl;
		std::cout << "Az alpaka evo szorny elfogyaszt egy alpakat es meghizik." << std::endl;
		std::cout << std::endl;

		std::cout << "Az alpaka ujjaszuletik." << std::endl;
		std::cout << std::endl;

		setMonsterSteps = true;
		numberOfMonsterMeal++;

		a->ReBorn(GetNewPosition());
		numberOfAlpacaReborn++;

	}
	else if (dynamic_cast<Alpaca*>(currentPlayer) && dynamic_cast<Monster*>(otherPlayer))
	{
		Alpaca* a = dynamic_cast<Alpaca*>(currentPlayer);
		Monster* m = dynamic_cast<Monster*>(otherPlayer);

		std::cout << std::endl;
		std::cout << "Az alpaka evo szorny elfogyaszt egy alpakat es meghizik." << std::endl;
		std::cout << std::endl;

		std::cout << "Az alpaka ujjaszuletik." << std::endl;
		std::cout << std::endl;

		setMonsterSteps = true;
		numberOfMonsterMeal++;

		a->ReBorn(GetNewPosition());
		numberOfAlpacaReborn++;

	}

}
