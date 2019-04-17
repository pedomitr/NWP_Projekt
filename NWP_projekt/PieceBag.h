#pragma once
#include "Piece.h"
class PieceBag
{
public:
	Piece current_piece = { {0, 0}, true, 0, 0 };
	Piece last_piece = { {0, 0}, true, 0, 0 };
	bool en_passant = false;
	int en_passant_ID = 0;
	POINT en_passant_x = { 0, 0 };
	bool en_passant_color = true;
	POINT en_passant_move = { 0, 0 };
	std::vector<Piece> pieces;
	void Initialize();
	bool CheckField(POINT field);
	PieceBag();
	~PieceBag();
};

