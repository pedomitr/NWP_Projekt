#include "stdafx.h"
#include "Field.h"
#include "Piece.h"


Field::Field(POINT position, bool color, Piece _piece)
{
	this->position = position;
	this->color = color;
	piece = _piece;
}


Field::~Field()
{
}
