#pragma once
#include "Piece.h"
class Queen :
	public Piece
{
private:
	TCHAR* name = _T("Q");
	POINT position;
	bool color;
public:
	Queen(POINT position, bool color);
	~Queen();
	POINT* PossibleMoves();
	void MoveTaken(POINT field);
};