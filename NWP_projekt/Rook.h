#pragma once
#include "Piece.h"
struct Rook : 
	public Piece
{
private:
	TCHAR* name = _T("R");
	POINT position;
	bool color;
public:
	Rook(POINT position, bool color);
	~Rook();
	POINT* PossibleMoves();
	void MoveTaken(POINT field);
};

