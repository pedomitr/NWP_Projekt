#pragma once

struct Piece
{
private:
	std::string name = "Piece";
	int pieceID = 0;
	int vectorID = 0;
	bool color = true;
public:
	Piece(POINT _position, bool _color, int _pieceID, int vectorID);
	~Piece();
	bool in_play = true;
	POINT position = { 0, 0 };
	int GetID() const { return pieceID; }
	void SetID(int ID) { pieceID = ID; }
	int GetVectorID() const { return vectorID; }
	std::string GetName() const { return name; }
	void SetName(std::string _name) { name = _name; }
	bool GetColor() const { return color; }
};

