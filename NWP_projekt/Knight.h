#pragma once
#include "Piece.h"
struct Knight :
	public Piece
{
private:
public:
	Knight(POINT position, bool color, int pieceID);
	~Knight();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};

