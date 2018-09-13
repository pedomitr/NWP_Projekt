#include "stdafx.h"
#include "Rook.h"


Rook::Rook(POINT _position, bool _color, int _pieceID)
{
	position = _position;
	color = _color;
	pieceID = _pieceID;
}


Rook::~Rook()
{
}

std::vector<POINT> Rook::PossibleMoves() {
	int i = 0;
	std::vector<POINT> moves;
	POINT temp;
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

void Rook::MoveTaken(POINT field)
{
	position = field;
}


