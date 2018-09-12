#pragma once
#include "Piece.h"
class Queen :
	public Piece
{
	TCHAR name;
	POINT position;
	bool color;
public:
	Queen(TCHAR name, POINT position, bool color);
	~Queen();
	POINT* PossibleMoves();
	void MoveTaken(POINT field);
};