#include "pch.h"
#include "Alpaca.h"
#include "time.h"
#include <iostream>


Alpaca::Alpaca()
{
}

Alpaca::Alpaca(Position p) : Character(p)
{
	initSteps();
	SetAllowedSteps(1);
}

Alpaca::Alpaca(Position p, Gift* g) : Character(p)
{
	initSteps();
	SetAllowedSteps(1);
	this->gift = g;
}

Alpaca::~Alpaca()
{
}

void Alpaca::Welcome(int type)
{
	if (type == 1)
		std::cout << "Szia!" << std::endl;
	else if (type == 2)
		std::cout << "Hello!" << std::endl;
}

void Alpaca::Move(const std::vector<Position>& validSteps, int tableSize, const std::vector<Position>& obstacles, int index)
{
	std::cout << "Alpaka" << index + 1  << " lep." << std::endl;

	Position newPosition;
	int moveNumber;
	bool repeatedStep = false;
	bool isObs = false;

	std::vector<int> randomSteps = { 0, 1, 2, 3 };
	int n = randomSteps.size();


	//Fisher-Yates suffle
	for (int i = 0; i < n - 1; i++)
	{
		int j = i + rand() % (n - i);
		std::swap(randomSteps[i], randomSteps[j]);
	}

	int i = 0;
	for (;;)
	{
		if (i == 4)
		{
			i = 0;
			this->steps.push_front(Position(-3, 3));
			this->steps.pop_back();
		}

		moveNumber = randomSteps[i];
		newPosition = this->GetPosition() + validSteps[moveNumber];

		repeatedStep = isSimilarStep(newPosition);
		isObs = this->isObstacle(newPosition, obstacles);

		if (newPosition.isValid(tableSize) && !repeatedStep && !isObs)
			break;

		i++;
	}

	this->SetPosition(newPosition);
	this->steps.push_front(newPosition);
	this->steps.pop_back();

}

void Alpaca::ChangeGift(Alpaca* a)
{
	Gift* temp = a->gift;
	a->gift = this->gift;
	this->gift = temp;
}

void Alpaca::ReBorn(Position p)
{
	SetPosition(p);
}

bool Alpaca::isSimilarStep(Position p)
{
	bool result = false;

	for (int i = 0; i < 4; i++)
	{
		if (steps[i] == p) {
			result = true;
			break;
		}
	}
	return result;
}

void Alpaca::initSteps()
{
	steps.clear();

	for (int i = 0; i < 4; i++)
	{
		Position p(-3, -3);
		steps.push_front(p);
	}
}

void Alpaca::ShowGift()
{
	this->gift->ToString();
}



