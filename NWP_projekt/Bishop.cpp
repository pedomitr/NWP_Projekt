#include "stdafx.h"
#include "Bishop.h"


Bishop::Bishop(POINT _position, bool _color)
{
	position = _position;
	color = _color;
}


Bishop::~Bishop()
{
}

POINT * Bishop::PossibleMoves()
{
	int i = 0, j = 0;
	POINT* moves = new POINT[13];
	for (; i < position.x  && i < (7 - position.y); ++i, ++j)
	{
		moves[j].x = position.x - (i + 1);
		moves[j].y = position.y + (i + 1);
	}
	for (i = 0; i < position.x && i < position.y; ++i, ++j)
	{
		moves[j].x = position.x - (i + 1);
		moves[j].y = position.y - (i + 1);
	}
	for (i = 0; i < (7 - position.x) && i < (7 - position.y); ++i, ++j)
	{
		moves[j].x = position.x + (i + 1);
		moves[j].y = position.y + (i + 1);
	}
	for (i = 0; i < (7 - position.x) && i < position.y; ++i, ++j)
	{
		moves[j].x = position.x + (i + 1);
		moves[j].y = position.y - (i + 1);
	}
	return moves;
}

void Bishop::MoveTaken(POINT field)
{
	position = field;
}
