#pragma once
#include "Piece.h"
class Bishop :
	public Piece
{
	TCHAR name;
	POINT position;
	bool color;
public:
	Bishop(TCHAR name, POINT position, bool color);
	~Bishop();
	POINT* PossibleMoves();
	void MoveTaken(POINT field);
};