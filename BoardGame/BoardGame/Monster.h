#pragma once
#include "Character.h"
class Monster :
	public Character
{
private:
	int numberOfFatRounds;

public:
	Monster();
	Monster(Position p);
	~Monster();

	virtual void Move(const std::vector<Position>& validSteps, int tableSize, const std::vector<Position>& obstacles, int index);
};

