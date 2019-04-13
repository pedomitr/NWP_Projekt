#include "stdafx.h"
#include "Piece.h"



Piece::Piece(POINT _position, bool _color, int _pieceID)
{
	position = _position;
	color = _color;
	pieceID = _pieceID;

	switch (_pieceID)
	{
	case 1:
	{
		name = "K";
		break;
	}
	case 2:
	{
		name = "Q";
		break;
	}
	case 3:
	{
		name = "R";
		break;
	}
	case 4:
	{
		name = "B";
		break;
	}
	case 5:
	{
		name = "N";
		break;
	}
	case 6:
	{
		name = "p";
		break;
	}
	default:
		name = "Piece";
	}	
}

Piece::~Piece()
{
}

