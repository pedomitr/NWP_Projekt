#pragma once
#include "Piece.h"
struct King :
	public Piece
{
private:
public:
	King(POINT position, bool color, int pieceID);
	~King();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};
