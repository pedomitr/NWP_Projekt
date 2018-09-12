#pragma once
#include "Piece.h"
struct Knight :
	public Piece
{
private:
	TCHAR* name = _T("N");
	POINT position;
	bool color;
public:
	Knight(POINT position, bool color);
	~Knight();
	POINT* PossibleMoves();
	void MoveTaken(POINT field);
};

