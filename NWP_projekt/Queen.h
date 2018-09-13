#pragma once
#include "Piece.h"
class Queen :
	public Piece
{
private:
	std::string name = "Q";
	POINT position;
	bool color;
public:
	Queen(POINT position, bool color);
	~Queen();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};