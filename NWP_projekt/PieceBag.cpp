#include "stdafx.h"
#include "PieceBag.h"
#include "Piece.h"


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
		if (pieces.at(i).in_play && p.x == field.x && p.y == field.y)
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
		Piece temp_p = { {p.x++, p.y}, true, 6 , i };
		pieces.push_back(temp_p);
	}
	p.x = 0;
	p.y = 0;
	Piece temp_p = { {p.x++, p.y}, true, 3, i++};
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, true, 5 , i++ };
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, true, 4, i++ };
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, true, 2, i++ };
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, true, 1, i++ };
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, true, 4, i++ };
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, true, 5, i++ };
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, true, 3, i++ };
	pieces.push_back(temp_p);

	//Black
	for ( p.x = 0, p.y = 6; i < 24; ++i)
	{
		Piece temp_p = { {p.x++, p.y}, false, 6, i };
		pieces.push_back(temp_p);
	}
	p.x = 0;
	p.y = 7;
	temp_p = { {p.x++, p.y}, false, 3, i++ };
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, false, 5, i++ };
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, false, 4, i++ };
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, false, 2, i++ };
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, false, 1, i++ };
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, false, 4, i++ };
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, false, 5, i++ };
	pieces.push_back(temp_p);
	temp_p = { {p.x++, p.y}, false, 3, i++ };
	pieces.push_back(temp_p);
}

