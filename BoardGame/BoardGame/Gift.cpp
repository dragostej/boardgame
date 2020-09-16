#include "pch.h"
#include "Gift.h"


Gift::Gift()
{
}

Gift::Gift(std::string name)
{
	this->name = name;
}


Gift::~Gift()
{
}

void Gift::ToString()
{
	std::cout << name << std::endl;
}
