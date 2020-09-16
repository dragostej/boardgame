#include "pch.h"
#include "Monster.h"


Monster::Monster()
{
}

Monster::Monster(Position p) : Character(p)
{
	SetAllowedSteps(3);
}

Monster::~Monster()
{
}

void Monster::Move(const std::vector<Position>& validSteps, int tableSize, const std::vector<Position>& obstacles, int index)
{
	std::cout << "Alpaka evo szorny lep." << std::endl;

	Position newPosition;
	int moveNumber;
	bool isObs = false;

	for (;;)
	{
		moveNumber = rand() % validSteps.size();
		newPosition = this->GetPosition() + validSteps[moveNumber];
		isObs = this->isObstacle(newPosition, obstacles);

		if (newPosition.isValid(tableSize) && !isObs)
			break;

	}

	this->SetPosition(newPosition);

}


