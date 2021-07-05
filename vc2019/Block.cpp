#include "Block.h"

Block::Block()
{
	ID = 0;
	metaData = "";
}

int Block::GetID()
{
    return ID;
}

void Block::SetID(int id)
{
	ID = id;
}
