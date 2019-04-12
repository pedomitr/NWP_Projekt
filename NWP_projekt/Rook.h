#pragma once
#include "Piece.h"
struct Rook :
	public Piece
{
private:
public:
	Rook(POINT position, bool color, int pieceID);
	~Rook();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};

