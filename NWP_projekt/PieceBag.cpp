#include "stdafx.h"
#include "PieceBag.h"


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