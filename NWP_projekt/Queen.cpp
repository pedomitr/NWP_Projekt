#include "stdafx.h"
#include "Queen.h"


Queen::Queen(POINT _position, bool _color)
{
	position = _position;
	color = _color;
}

Queen::~Queen()
{
}

POINT * Queen::PossibleMoves()
{
	int i = 0, j = 0;
	POINT* moves = new POINT[27];
	for (; i < position.x && i < (7 - position.y); ++i, ++j)
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

	for (i = 0; i < 8; ++i)
	{
		if (i == position.x) continue;
		moves[j].x = i;
		moves[j].y = position.y;
		++j;

	}
	for (i = 0; i < 8; ++i)
	{
		if (i == position.y) continue;
		moves[j].x = position.x;
		moves[j].y = i;
		++j;
	}
	return moves;
}


void Queen::MoveTaken(POINT field)
{
	position = field;
}
