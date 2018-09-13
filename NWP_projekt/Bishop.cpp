#include "stdafx.h"
#include "Bishop.h"


Bishop::Bishop(POINT _position, bool _color, int _pieceID)
{
	position = _position;
	color = _color;
	pieceID = _pieceID;
}


Bishop::~Bishop()
{
}

std::vector<POINT> Bishop::PossibleMoves()
{
	int i = 0;
	std::vector<POINT> moves;
	POINT temp;
	for (; i < position.x && i < (7 - position.y); ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = position.y + (i + 1);
		moves.push_back(temp);
	}
	for (i = 0; i < position.x && i < position.y; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = position.y - (i + 1);
		moves.push_back(temp);
	}
	for (i = 0; i < (7 - position.x) && i < (7 - position.y); ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = position.y + (i + 1);
		moves.push_back(temp);
	}
	for (i = 0; i < (7 - position.x) && i < position.y; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = position.y - (i + 1);
		moves.push_back(temp);
	}
	return moves;
}

void Bishop::MoveTaken(POINT field)
{
	position = field;
}
