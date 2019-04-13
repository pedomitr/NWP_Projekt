#pragma once
class Figure
{
//jedinice za ucitavanje pojedinih figura
public:
	double piece_width = (double)1 / 6;
	double piece_height = (double)1 / 2;
	double white_piece = 0;
	double black_piece = (double)1 / 2;
	double king = 0;
	double queen = (double)1 / 6;
	double bishop = (double)2 / 6;
	double knight = (double)3 / 6;
	double rook = (double)4 / 6;
	double pawn = (double)5 / 6;
	COLORREF transparent = RGB(120, 120, 120);
public:
	Figure();
	~Figure();
};

