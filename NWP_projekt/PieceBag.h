#pragma once
#include "Piece.h"
class PieceBag
{
public:
	Piece current_piece;
	std::vector<Piece> pieces;
	void Initialize();
	bool CheckField(POINT field);
	PieceBag();
	~PieceBag();
};

