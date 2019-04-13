#pragma once
#include "Piece.h"
class PieceBag
{
public:
	Piece current_piece = { {0, 0}, true, 0 };
	std::vector<Piece> pieces;
	void Initialize();
	bool CheckField(POINT field);
	PieceBag();
	~PieceBag();
};

