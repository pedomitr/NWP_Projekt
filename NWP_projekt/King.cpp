#include "stdafx.h"
#include "King.h"


King::King(POINT _position, bool _color)
{
	position = _position;
	color = _color;
}

King::~King()
{
}

POINT * King::PossibleMoves()
{
	int i = 0, j = 0;
	POINT* moves = new POINT[8];
	if (position.x > 0 && position.y < 7)
	{
		moves[j].x = position.x - 1;
		moves[j].y = position.y + 1;
		++j;
	}
	if (position.x > 0 && position.y > 0)
	{
		moves[j].x = position.x - 1;
		moves[j].y = position.y - 1;
		++j;
	}
	if (position.x < 7 && position.y < 7)
	{
		moves[j].x = position.x + 1;
		moves[j].y = position.y + 1;
		++j;
	}
	if (position.x < 7 && position.y > 0)
	{
		moves[j].x = position.x + 1;
		moves[j].y = position.y - 1;
		++j;
	}

	if (position.x > 0 )
	{
		moves[j].x = position.x - 1;
		moves[j].y = position.y;
		++j;
	}
	if (position.x < 7)
	{
		moves[j].x = position.x + 1;
		moves[j].y = position.y;
		++j;
	}
	if (position.y < 7)
	{
		moves[j].x = position.x ;
		moves[j].y = position.y + 1;
		++j;
	}
	if (position.y > 0)
	{
		moves[j].x = position.x;
		moves[j].y = position.y - 1;
		++j;
	}
	return moves;
}

void King::MoveTaken(POINT field)
{
	position = field;
}
