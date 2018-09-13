#include "stdafx.h"
#include "Pawn.h"


Pawn::Pawn(POINT _position, bool _color, int _pieceID)
{
	position = _position;
	color = _color;
	pieceID = _pieceID;
}


Pawn::~Pawn()
{
}

std::vector<POINT> Pawn::PossibleMoves()
{
	std::vector<POINT> moves;
	POINT temp;
	if (color)
	{
		if (position.y == 1)
		{
			temp.x = position.x;
			temp.y = position.y + 2;
			moves.push_back(temp);
		}
		temp.x = position.x;
		temp.y = position.y + 1;
		moves.push_back(temp);
	}
	if (!color)
	{
		if (position.y == 6)
		{
			temp.x = position.x;
			temp.y = position.y - 2;
			moves.push_back(temp);
		}
		temp.x = position.x;
		temp.y = position.y - 1;
		moves.push_back(temp);
	}
	//Dodati ako postoje figure suprotne boje za pojesti i en passan
	return moves;
}

void Pawn::MoveTaken(POINT field)
{
	position = field;
}
