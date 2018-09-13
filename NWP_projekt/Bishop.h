#pragma once
#include "Piece.h"
struct Bishop :
	public Piece
{
private:
	std::string name = "B";
	POINT position;
	bool color;
public:
	Bishop(POINT position, bool color);
	~Bishop();
	std::vector<POINT> PossibleMoves();
	void MoveTaken(POINT field);
};