#pragma once
#include <string>

class Block
{
	std::string metaData;
	int ID;
public:
	Block();
	int GetID();
	void SetID(int id);
};

