#pragma once
#include "Piece.h"
struct Bishop :
	public Piece
{
private:
public:
	Bishop(POINT position, bool color, int pieceID);
	~Bishop();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};