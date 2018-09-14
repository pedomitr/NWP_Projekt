#pragma once
#include "Piece.h"
struct Pawn :
	public Piece
{
public:
	std::string name = "P";
	POINT position;
	bool color;
	int pieceID;
public:
	Pawn(POINT position, bool color, int pieceID);
	~Pawn();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};
