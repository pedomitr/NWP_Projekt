#pragma once
#include "Piece.h"
struct Rook : 
	public Piece
{
private:
	std::string name = "R";
	POINT position;
	bool color;
	int pieceID;
public:
	Rook(POINT position, bool color, int pieceID));
	~Rook();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};

