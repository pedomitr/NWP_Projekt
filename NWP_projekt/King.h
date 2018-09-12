#pragma once
#include "Piece.h"
class King :
	public Piece
{
	TCHAR name;
	POINT position;
	bool color;
public:
	King(TCHAR name, POINT position, bool color);
	~King();
	POINT* PossibleMoves();
	void MoveTaken(POINT field);
};
