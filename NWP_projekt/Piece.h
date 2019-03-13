#pragma once

struct Piece
{
public:
	Piece();
	~Piece();
	virtual std::vector<POINT> PossibleMoves();
	virtual void MoveTaken(POINT field);
};

