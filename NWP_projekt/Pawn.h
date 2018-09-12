#pragma once
#include "Piece.h"
class Pawn :
	public Piece
{
	TCHAR name;
	POINT position;
	bool color;
public:
	Pawn(TCHAR name, POINT position, bool color);
	~Pawn();
	POINT* PossibleMoves();
	void MoveTaken(POINT field);
};
