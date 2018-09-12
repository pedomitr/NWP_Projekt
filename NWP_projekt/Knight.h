#pragma once
#include "Piece.h"
class Knight :
	public Piece
{
	TCHAR name;
	POINT position;
	bool color;
public:
	Knight(TCHAR name, POINT position, bool color));
	~Knight();
	POINT* PossibleMoves();
	void MoveTaken(POINT field);
};

