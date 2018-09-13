#include "stdafx.h"
#include "Queen.h"


Queen::Queen(POINT _position, bool _color, int _pieceID)
{
	position = _position;
	color = _color;
	pieceID = _pieceID;
}

Queen::~Queen()
{
}

std::vector<POINT> Queen::PossibleMoves()
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

	for (i = 0; i < 8; ++i)
	{
		if (i == position.x) continue;
		temp.x = i;
		temp.y = position.y;
		moves.push_back(temp);

	}
	for (i = 0; i < 8; ++i)
	{
		if (i == position.y) continue;
		temp.x = position.x;
		temp.y = i;
		moves.push_back(temp);
	}
	return moves;
}


void Queen::MoveTaken(POINT field)
{
	position = field;
}
