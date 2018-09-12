#pragma once
#include "Piece.h"
struct Pawn :
	public Piece
{
private:
	TCHAR* name = _T("P");
	POINT position;
	bool color;
public:
	Pawn(POINT position, bool color);
	~Pawn();
	POINT* PossibleMoves();
	void MoveTaken(POINT field);
};
