#pragma once

struct Piece
{
protected:
	std::string name = "C";
	int pieceID = 0;
public:
	Piece();
	~Piece();
	bool color = true;
	POINT position = { 0, 0 };
	int GetID() const { return pieceID; }
	std::vector<Piece> pieces;
	virtual std::vector<POINT> PossibleMoves();
	virtual void MoveTaken(POINT field);
};

