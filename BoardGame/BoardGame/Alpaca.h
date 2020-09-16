#pragma once
#include "Character.h"
#include "Gift.h"
#include <vector>
#include <deque>

class Alpaca :
	public Character
{
private:
	std::deque<Position> steps;
	Gift* gift;

public:
	Alpaca();
	Alpaca(Position p);
	Alpaca(Position p, Gift *g);
	~Alpaca();

	void Welcome(int type);
	virtual void Move(const std::vector<Position>& validSteps, int tableSize, const std::vector<Position>& obstacles, int index);
	void ChangeGift(Alpaca* a);
	void ReBorn(Position p);
	bool isSimilarStep(Position p);
	void initSteps();
	void ShowGift();

};

