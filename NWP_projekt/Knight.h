#pragma once
#include "Piece.h"
struct Knight :
	public Piece
{
private:
	std::string name = "N";
	POINT position;
	bool color;
	int pieceID;
public:
	Knight(POINT position, bool color, int pieceID));
	~Knight();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};

