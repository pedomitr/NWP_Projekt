#pragma once

struct Piece
{
protected:
	std::string name = "Piece";
	int pieceID = 0;
	bool color = true;
public:
	Piece(POINT _position, bool _color, int _pieceID);
	~Piece();
	POINT position = { 0, 0 };
	int GetID() const { return pieceID; }
	std::string GetName() const { return name; }
	bool GetColor() const { return color; }
};

