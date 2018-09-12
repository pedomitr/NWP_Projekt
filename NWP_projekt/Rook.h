#pragma once
#include "Piece.h"
class Rook : public Piece
{
	TCHAR name;
	POINT position;
	bool color;
public:
	Rook(TCHAR name, POINT position, bool color);
	~Rook();
	POINT* PossibleMoves();
	void MoveTaken(POINT field);
};

