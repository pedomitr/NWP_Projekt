#pragma once

struct Piece
{
protected:
	std::string name = "C";
	POINT position = { 0, 0 };
	bool color = true;
	int pieceID = 0;
public:
	Piece();
	~Piece();
	virtual std::vector<POINT> PossibleMoves();
	virtual void MoveTaken(POINT field);
};

