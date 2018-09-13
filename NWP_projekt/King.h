#pragma once
#include "Piece.h"
struct King :
	public Piece
{
private:
	std::string name = "K";
	POINT position;
	bool color;
	int pieceID;
public:
	King(POINT position, bool color, int pieceID);
	~King();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};
