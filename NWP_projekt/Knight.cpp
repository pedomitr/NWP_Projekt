#include "stdafx.h"
#include "Knight.h"


Knight::Knight(POINT _position, bool _color, int _pieceID)
{
	position = _position;
	color = _color;
	pieceID = _pieceID;
}


Knight::~Knight()
{
}

std::vector<POINT> Knight::PossibleMoves()
{
	std::vector<POINT> moves;
	POINT temp;
	if (position.x > 0 && position.y < 6)
	{
		temp.x = position.x - 1;
		temp.y = position.y + 2;
		moves.push_back(temp);
	}
	if (position.x > 0 && position.y > 1)
	{
		temp.x = position.x - 1;
		temp.y = position.y - 2;
		moves.push_back(temp);
	}
	if (position.x < 7 && position.y < 6)
	{
		temp.x = position.x + 1;
		temp.y = position.y + 2;
		moves.push_back(temp);
	}
	if (position.x < 7 && position.y > 1)
	{
		temp.x = position.x + 1;
		temp.y = position.y - 2;
		moves.push_back(temp);
	}

	if (position.x > 1 && position.y < 7)
	{
		temp.x = position.x - 2;
		temp.y = position.y + 1;
		moves.push_back(temp);
	}
	if (position.x > 1 && position.y > 0)
	{
		temp.x = position.x - 2;
		temp.y = position.y - 1;
		moves.push_back(temp);
	}
	if (position.x < 6 && position.y < 7)
	{
		temp.x = position.x + 2;
		temp.y = position.y + 1;
		moves.push_back(temp);
	}
	if (position.x < 6 && position.y > 0)
	{
		temp.x = position.x + 2;
		temp.y = position.y - 1;
		moves.push_back(temp);
	}
	return moves;
}

void Knight::MoveTaken(POINT field)
{
	position = field;
}
