#include "stdafx.h"
#include "Moves.h"


Moves::Moves()
{
}


Moves::~Moves()
{
}

std::vector<POINT> Moves::PossibleMoves(int pieceID, POINT position, bool color)
{
	std::vector<POINT> moves;
	switch (pieceID)
	{
		case 1:
		{
			moves = KingMoves(position);
			break;
		}
		case 2:
		{
			moves = QueenMoves(position);
			break;
		}
		case 3:
		{
			moves = RookMoves(position);
			break;
		}
		case 4:
		{
			moves = BishopMoves(position);
			break;
		}
		case 5:
		{
			moves = KnightMoves(position);
			break;
		}
		case 6:
		{
			moves = PawnMoves(position, color);
			break;
		}
		default:
		{

		}
	}
	return moves;
}

std::vector<POINT> Moves::KingMoves(POINT position)
{
	std::vector<POINT> moves;
	POINT temp;
	if (position.x > 0 && position.y < 7)
	{
		temp.x = position.x - 1;
		temp.y = 7 - (position.y + 1);
		moves.push_back(temp);
	}
	if (position.x > 0 && position.y > 0)
	{
		temp.x = position.x - 1;
		temp.y = 7 - (position.y - 1);
		moves.push_back(temp);
	}
	if (position.x < 7 && position.y < 7)
	{
		temp.x = position.x + 1;
		temp.y = 7 - (position.y + 1);
		moves.push_back(temp);
	}
	if (position.x < 7 && position.y > 0)
	{
		temp.x = position.x + 1;
		temp.y = 7 - (position.y - 1);
		moves.push_back(temp);
	}

	if (position.x > 0)
	{
		temp.x = position.x - 1;
		temp.y = 7 - position.y;
		moves.push_back(temp);
	}
	if (position.x < 7)
	{
		temp.x = position.x + 1;
		temp.y = 7 - position.y;
		moves.push_back(temp);
	}
	if (position.y < 7)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y + 1);
		moves.push_back(temp);
	}
	if (position.y > 0)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y - 1);
		moves.push_back(temp);
	}
	return moves;
}

std::vector<POINT> Moves::QueenMoves(POINT position)
{
	std::vector<POINT> moves;
	POINT temp;
	int i = 0;
	for (i = 0; i < position.x && i < (7 - position.y); ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		moves.push_back(temp);
	}
	for (i = 0; i < position.x && i < position.y; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		moves.push_back(temp);
	}
	for (i = 0; i < (7 - position.x) && i < (7 - position.y); ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		moves.push_back(temp);
	}
	for (i = 0; i < (7 - position.x) && i < position.y; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		moves.push_back(temp);
	}

	for (i = 0; i < 8; ++i)
	{
		if (i == position.x) continue;
		temp.x = i;
		temp.y = 7 - position.y;
		moves.push_back(temp);

	}
	for (i = 0; i < 8; ++i)
	{
		if (i == position.y) continue;
		temp.x = position.x;
		temp.y = 7 - i;
		moves.push_back(temp);
	}
	return moves;
}

std::vector<POINT> Moves::RookMoves(POINT position)
{
	std::vector<POINT> moves;
	POINT temp;
	int i = 0;
	for (i = 0; i < 8; ++i)
	{
		if (i == position.x) continue;
		temp.x = i;
		temp.y = 7 - position.y;
		moves.push_back(temp);
	}
	for (i = 0; i < 8; ++i)
	{
		if (i == position.y) continue;
		temp.x = position.x;
		temp.y = 7 - i;
		moves.push_back(temp);
	}
	return moves;
}

std::vector<POINT> Moves::BishopMoves(POINT position)
{
	std::vector<POINT> moves;
	POINT temp;
	int i = 0;
	for (; i < position.x && i < (7 - position.y); ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		moves.push_back(temp);
	}
	for (i = 0; i < position.x && i < position.y; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		moves.push_back(temp);
	}
	for (i = 0; i < (7 - position.x) && i < (7 - position.y); ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		moves.push_back(temp);
	}
	for (i = 0; i < (7 - position.x) && i < position.y; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		moves.push_back(temp);
	}
	return moves;
}

std::vector<POINT> Moves::KnightMoves(POINT position)
{
	std::vector<POINT> moves;
	POINT temp;
	if (position.x > 0 && position.y < 6)
	{
		temp.x = position.x - 1;
		temp.y = 7 - (position.y + 2);
		moves.push_back(temp);
	}
	if (position.x > 0 && position.y > 1)
	{
		temp.x = position.x - 1;
		temp.y = 7 - (position.y - 2);
		moves.push_back(temp);
	}
	if (position.x < 7 && position.y < 6)
	{
		temp.x = position.x + 1;
		temp.y = 7 - (position.y + 2);
		moves.push_back(temp);
	}
	if (position.x < 7 && position.y > 1)
	{
		temp.x = position.x + 1;
		temp.y = 7 - (position.y - 2);
		moves.push_back(temp);
	}
	if (position.x > 1 && position.y < 7)
	{
		temp.x = position.x - 2;
		temp.y = 7 - (position.y + 1);
		moves.push_back(temp);
	}
	if (position.x > 1 && position.y > 0)
	{
		temp.x = position.x - 2;
		temp.y = 7 - (position.y - 1);
		moves.push_back(temp);
	}
	if (position.x < 6 && position.y < 7)
	{
		temp.x = position.x + 2;
		temp.y = 7 - (position.y + 1);
		moves.push_back(temp);
	}
	if (position.x < 6 && position.y > 0)
	{
		temp.x = position.x + 2;
		temp.y = 7 - (position.y - 1);
		moves.push_back(temp);
	}
	return moves;
}

std::vector<POINT> Moves::PawnMoves(POINT position, bool color)
{
	std::vector<POINT> moves;
	POINT temp;
	if (color)
	{
		if (position.y == 1)
		{
			temp.x = position.x;
			temp.y = 7 -( position.y + 2);
			moves.push_back(temp);
		}
		temp.x = position.x;
		temp.y = 7 - (position.y + 1);
		moves.push_back(temp);
	}
	if (!color)
	{
		if (position.y == 6)
		{
			temp.x = position.x;
			temp.y = 7 -  (position.y - 2);
			moves.push_back(temp);
		}
		temp.x = position.x;
		temp.y = 7 - (position.y - 1);
		moves.push_back(temp);
	}
	//Dodati ako postoje figure suprotne boje za pojesti i en passan
	return moves;
}

bool Moves::GetFieldColor(POINT p_field)
{
	if (p_field.x % 2 == 0)
	{
		if (p_field.y % 2 == 0) return false;
		return true;
	}
	else
		if (p_field.y % 2 == 0) return true;
	return false;
}
