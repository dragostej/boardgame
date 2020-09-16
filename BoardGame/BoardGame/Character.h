#include "Position.h"
#include <vector>

#pragma once
class Character
{

private:
	Position currentPosition;
	int allowedSteps;
public:
	Character();
	Character(Position p);
	virtual ~Character();
	virtual void Move(const std::vector<Position>& validSteps, int tableSize, const std::vector<Position>& obstacles, int index);
	void PrintPosition();
	Position GetPosition();
	void SetPosition(Position newPosition);
	bool isObstacle(Position p, const std::vector<Position>& obstacles);
	int GetAllowedSteps();
	void SetAllowedSteps(int allowedSteps);

};

