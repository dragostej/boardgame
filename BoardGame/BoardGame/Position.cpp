#include "pch.h"
#include "Position.h"


Position::Position()
{
}

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

Position::Position(int x, int y, char type)
{
	this->x = x;
	this->y = y;
	this->type = type;
}

Position::Position(const Position &p)
{
	this->x = p.x;
	this->y = p.y;
	this->type = p.type;
}

Position::~Position()
{
}

bool Position::operator==(Position const &other)
{
	return this->x == other.x && this->y == other.y ? true : false;
}

bool Position::operator==(Position const &other) const
{
	return this->x == other.x && this->y == other.y ? true : false;
}



Position Position::operator+(Position const &other)
{
	return Position(this->x + other.x, this->y + other.y);
}

void Position::ToString()
{
	std::cout << this->x << " " << this->y << std::endl;
}

int Position::GetX()
{
	return this->x;
}

int Position::GetY()
{
	return this->y;
}

void Position::SetX(int x)
{
	this->x = x;
}

void Position::SetY(int y)
{
	this->y = y;
}

void Position::PrintType()
{
	std::cout << this->type << std::endl;
}

char Position::GetType()
{
	return this->type;
}

void Position::SetType(char type)
{
	this->type = type;
}

bool Position::isValid(int tableSize)
{
	if (this->x > 0 && this->x <= tableSize && this->y > 0 && this->y <= tableSize)
		return true;
	else return false;
}
