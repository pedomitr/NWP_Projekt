#pragma once
#include "Piece.h"
struct King :
	public Piece
{
private:
	std::string name = "K";
	POINT position;
	bool color;
public:
	King(POINT position, bool color);
	~King();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};
