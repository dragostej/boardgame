#include <string>
#include<iostream>

#pragma once
class Position
{
private:
	int x, y;
	char type;

public:
	Position();
	Position(int x, int y);
	Position(int x, int y, char type);
	Position(const Position &p);
	~Position();

	bool operator==(Position const &other);
	bool operator==(Position const & other) const;
	Position operator+(Position const &other);
	void ToString();
	int GetX();
	int GetY();
	void SetX(int x);
	void SetY(int y);
	void PrintType();
	char GetType();
	void SetType(char type);
	bool isValid(int tableSize);
};

