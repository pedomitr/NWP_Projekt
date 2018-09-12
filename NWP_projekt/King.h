#pragma once
#include "Piece.h"
struct King :
	public Piece
{
private:
	TCHAR* name = _T("K");
	POINT position;
	bool color;
public:
	King(POINT position, bool color);
	~King();
	POINT* PossibleMoves();
	void MoveTaken(POINT field);
};
