#pragma once
class Figure_2
{
//jedinice za ucitavanje pojedinih figura
public:
	double piece_width = (double)1 / 6;
	double piece_height = (double)1 / 2;
	double white_piece = (double)1 / 2;
	double black_piece = 0;
	double king = 0;
	double queen = (double)1 / 6;
	double rook = (double)2 / 6;
	double bishop = (double)3 / 6;
	double knight = (double)4 / 6;
	double pawn = (double)5 / 6;
public:
	Figure_2();
	~Figure_2();
};

