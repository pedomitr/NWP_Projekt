#pragma once
#include "Piece.h"
struct Pawn :
	public Piece
{
public:
	std::string name = "P";
	POINT position;
	bool color;
public:
	Pawn(POINT position, bool color);
	~Pawn();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};
