#pragma once
#include "Piece.h"
struct Bishop :
	public Piece
{
private:
	TCHAR* name = _T("B");
	POINT position;
	bool color;
public:
	Bishop(POINT position, bool color);
	~Bishop();
	POINT* PossibleMoves();
	void MoveTaken(POINT field);
};