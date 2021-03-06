#pragma once
#include "Piece.h"
class PieceBag
{
public:
	Piece current_piece = { {0, 0}, true, 0, 0 };
	Piece last_piece = { {0, 0}, true, 0, 0 };
	std::vector<Piece> pieces;
	void Initialize();
	bool CheckField(POINT field);
	void Promote(int newID, PieceBag* bag);
	PieceBag();
	~PieceBag();
};

