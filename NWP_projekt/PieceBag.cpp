#include "stdafx.h"
#include "PieceBag.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"


PieceBag::PieceBag()
{
}


PieceBag::~PieceBag()
{
}

bool PieceBag::CheckField(POINT field)
{
	int i = 0;
	POINT p = { 0, 0 };
	while(i < pieces.size() )
	{
		p = pieces.at(i).position;
		if (p.x == field.x && p.y == field.y)
		{
			current_piece = pieces.at(i);
			return true;
		}
		++i;
	}
	return false;//empty field

}

void PieceBag::Initialize() 
{
	POINT p = { 0,0 };
	int i = 0;
	//White
	for (p.y = 1; i < 8; ++i)
	{
		Pawn temp_p = { {p.x++, p.y}, true, i };
		pieces.push_back(temp_p);
	}
	p.x = 0;
	p.y = 0;
	Rook temp_r = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_r);
	Knight temp_n = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_n);
	Bishop temp_b = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_b);
	Queen temp_q = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_q);
	King temp_k = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_k);
	temp_b = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_b);
	temp_n = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_n);
	temp_r = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_r);

	//Black
	for (p.x = 0, p.y = 6; i < 24; ++i)
	{
		Pawn temp_p = { {p.x++, p.y}, false, i };
		pieces.push_back(temp_p);
	}
	p.x = 0;
	p.y = 7;
	temp_r = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_r);
	temp_n = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_n);
	temp_b = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_b);
	temp_q = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_q);
	temp_k = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_k);
	temp_b = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_b);
	temp_n = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_n);
	temp_r = { {p.x++, p.y}, true, i++ };
	pieces.push_back(temp_r);
}