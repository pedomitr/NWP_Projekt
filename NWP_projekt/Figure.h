#pragma once
class Figure
{
	//jedinice za ucitavanje pojedinih figura
	//white/bijele
public:
	int piece_width = 1 / 6;
	int piece_height = 1 / 2;
	int white_piece = 0;
	int black_piece = 1 / 2;
	int king = 0;
	int queen = 1 / 6;
	int bishop = 2 / 6;
	int knight = 3 / 6;
	int rook = 4 / 6;
	int pawn = 5 / 6;
public:
	Figure();
	~Figure();
};

