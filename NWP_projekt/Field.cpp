#include "stdafx.h"
#include "Field.h"
#include "Piece.h"


Field::Field(POINT position, bool color, int pieceID)
{
	this->position = position;
	this->color = color;
	this->pieceID = pieceID;
}


Field::~Field()
{
}
