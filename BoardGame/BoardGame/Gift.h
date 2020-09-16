#include <string>
#include <iostream>

#pragma once
class Gift
{
private:
	std::string name;
public:
	Gift();
	Gift(std::string name);
	~Gift();

	void ToString();

};

