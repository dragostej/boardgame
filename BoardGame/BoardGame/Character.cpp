#include "pch.h"
#include "Character.h"


Character::Character()
{
}


Character::~Character()
{
}

Character::Character(Position p) : currentPosition(p)
{
	allowedSteps = 1;
}

void Character::PrintPosition()
{
	this->currentPosition.ToString();
}

Position Character::GetPosition()
{
	return this->currentPosition;
}

void Character::SetPosition(Position newPosition)
{
	this->currentPosition.SetX(newPosition.GetX());
	this->currentPosition.SetY(newPosition.GetY());
}

bool Character::isObstacle(Position p, const std::vector<Position>& obstacles)
{
	bool result = false;

	for (size_t i = 0; i < obstacles.size(); i++)
	{
		if (obstacles[i] == p) {
			result = true;
			break;
		}
	}
	return result;
}

int Character::GetAllowedSteps()
{
	return this->allowedSteps;
}

void Character::SetAllowedSteps(int allowedSteps)
{
	this->allowedSteps = allowedSteps;
}



void Character::Move(const std::vector<Position>& validSteps, int tableSize, const std::vector<Position>& obstacles, int index)
{
	std::cout << "lép" << std::endl;
}