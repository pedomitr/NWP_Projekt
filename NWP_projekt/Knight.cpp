#include "stdafx.h"
#include "Knight.h"


Knight::Knight(TCHAR _name, POINT _position, bool _color)
{
	name = _name;
	position = _position;
	color = _color;
}


Knight::~Knight()
{
}

POINT * Knight::PossibleMoves()
{
	int i = 0;
	POINT* moves;
	if (position.x > 0 && position.y < 6)
	{
		moves[i].x = position.x - 1;
		moves[i].y = position.y + 2;
		++i;
	}
	if (position.x > 0 && position.y > 1)
	{
		moves[i].x = position.x - 1;
		moves[i].y = position.y - 2;
		++i;
	}
	if (position.x < 7 && position.y < 6)
	{
		moves[i].x = position.x + 1;
		moves[i].y = position.y + 2;
		++i;
	}
	if (position.x < 7 && position.y > 1)
	{
		moves[i].x = position.x + 1;
		moves[i].y = position.y - 2;
		++i;
	}

	if (position.x > 1 && position.y < 7)
	{
		moves[i].x = position.x - 2;
		moves[i].y = position.y + 1;
		++i;
	}
	if (position.x > 1 && position.y > 0)
	{
		moves[i].x = position.x - 2;
		moves[i].y = position.y - 1;
		++i;
	}
	if (position.x < 6 && position.y < 7)
	{
		moves[i].x = position.x + 2;
		moves[i].y = position.y + 1;
		++i;
	}
	if (position.x < 6 && position.y > 0)
	{
		moves[i].x = position.x + 2;
		moves[i].y = position.y - 1;
		++i;
	}
	return moves;
}

void Knight::MoveTaken(POINT field)
{
	position = field;
}
