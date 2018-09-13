#pragma once
#include "Piece.h"
struct Rook : 
	public Piece
{
private:
	std::string name = "R";
	POINT position;
	bool color;
public:
	Rook(POINT position, bool color);
	~Rook();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};

