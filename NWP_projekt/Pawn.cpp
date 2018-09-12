#include "stdafx.h"
#include "Pawn.h"


Pawn::Pawn(POINT _position, bool _color)
{
	position = _position;
	color = _color;
}


Pawn::~Pawn()
{
}

POINT * Pawn::PossibleMoves()
{
	int j = 0;
	POINT* moves = new POINT[4];
	if (color)
	{
		if (position.y == 1)
		{
			moves[j].x = position.x;
			moves[j].y = position.y + 2;
			++j;
		}
		moves[j].x = position.x;
		moves[j].y = position.y + 1;
	}
	if (!color)
	{
		if (position.y == 6)
		{
			moves[j].x = position.x;
			moves[j].y = position.y - 2;
			++j;
		}
		moves[j].x = position.x;
		moves[j].y = position.y - 1;
	}
	//Dodati ako postoje figure suprotne boje za pojesti i en passan
	return moves;
}

void Pawn::MoveTaken(POINT field)
{
	position = field;
}
