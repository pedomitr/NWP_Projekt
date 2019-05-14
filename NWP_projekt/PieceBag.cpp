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
	pieces.clear();
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

void PieceBag::Promote(int newID, PieceBag* bag)
{
	int vectorID = bag->last_piece.GetVectorID();
	switch (newID)
	{
		case 1:
		{
			bag->pieces.at(vectorID).SetID(5);
			bag->pieces.at(vectorID).SetName("N");
			break;
		}
		case 2:
		{
			bag->pieces.at(vectorID).SetID(4);
			bag->last_piece.SetName("B");
			break;
		}
		case 3:
		{
			bag->pieces.at(vectorID).SetID(3);
			bag->pieces.at(vectorID).SetName("R");
			break;
		}
		case 4:
		{
			bag->pieces.at(vectorID).SetID(2);
			bag->pieces.at(vectorID).SetName("Q");
			break;
		}
		default:
			bag->pieces.at(vectorID).SetID(6);
			bag->pieces.at(vectorID).SetName("p");
	}
	bag->last_piece = bag->pieces.at(vectorID);
}

