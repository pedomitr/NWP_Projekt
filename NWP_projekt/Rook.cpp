#include "stdafx.h"
#include "Rook.h"


Rook::Rook(TCHAR _name, POINT _position, bool _color)
{
	name = _name;
	position = _position;
	color = _color;
}


Rook::~Rook()
{
}

POINT* Rook::PossibleMoves() {
	int i = 0, j = 0;
	POINT* moves;
	for (; i < 8 ; ++i)
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

void Rook::MoveTaken(POINT field)
{
	position = field;
}


