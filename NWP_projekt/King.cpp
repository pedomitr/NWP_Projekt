#include "stdafx.h"
#include "King.h"


King::King(POINT _position, bool _color, int _pieceID)
{
	position = _position;
	color = _color;
	pieceID = _pieceID;
}

King::~King()
{
}

std::vector<POINT> King::PossibleMoves()
{
	std::vector<POINT> moves;
	POINT temp;
	if (position.x > 0 && position.y < 7)
	{
		temp.x = position.x - 1;
		temp.y = position.y + 1;
		moves.push_back(temp);
	}
	if (position.x > 0 && position.y > 0)
	{
		temp.x = position.x - 1;
		temp.y = position.y - 1;
		moves.push_back(temp);
	}
	if (position.x < 7 && position.y < 7)
	{
		temp.x = position.x + 1;
		temp.y = position.y + 1;
		moves.push_back(temp);
	}
	if (position.x < 7 && position.y > 0)
	{
		temp.x = position.x + 1;
		temp.y = position.y - 1;
		moves.push_back(temp);
	}

	if (position.x > 0 )
	{
		temp.x = position.x - 1;
		temp.y = position.y;
		moves.push_back(temp);
	}
	if (position.x < 7)
	{
		temp.x = position.x + 1;
		temp.y = position.y;
		moves.push_back(temp);
	}
	if (position.y < 7)
	{
		temp.x = position.x ;
		temp.y = position.y + 1;
		moves.push_back(temp);
	}
	if (position.y > 0)
	{
		temp.x = position.x;
		temp.y = position.y - 1;
		moves.push_back(temp);
	}
	return moves;
}

void King::MoveTaken(POINT field)
{
	position = field;
}
