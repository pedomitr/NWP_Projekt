#pragma once
#include "Piece.h"
class Queen :
	public Piece
{
private:
public:
	Queen(POINT position, bool color, int pieceID);
	~Queen();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};