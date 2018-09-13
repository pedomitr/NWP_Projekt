#pragma once
#include "Piece.h"
class Queen :
	public Piece
{
private:
	std::string name = "Q";
	POINT position;
	bool color;
	int pieceID;
public:
	Queen(POINT position, bool color, int pieceID));
	~Queen();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};