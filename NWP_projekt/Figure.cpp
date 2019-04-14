#include "stdafx.h"
#include "Figure.h"



Figure::Figure()
{
}


Figure::~Figure()
{
}


double Figure::GetByID(int pieceID)
{
	switch (pieceID)
	{
	case 1:
	{
		return king;
	}
	case 2:
	{
		return queen;
	}
	case 3:
	{
		return rook;
	}
	case 4:
	{
		return bishop;
	}
	case 5:
	{
		return knight;
	}
	case 6:
	{
		return pawn;
	}
	}
	return 0;
}


double Figure::GetColor(bool color)
{
	if (color) return white_piece;
	return black_piece;
}
