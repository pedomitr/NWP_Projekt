#pragma once
#include "Piece.h"
struct Pawn :
	public Piece
{
public:
public:
	Pawn(POINT position, bool color, int pieceID);
	~Pawn();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};
