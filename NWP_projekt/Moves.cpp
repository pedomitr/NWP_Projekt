#include "stdafx.h"
#include "Moves.h"
#include <algorithm>

Moves::Moves()
{
}


Moves::~Moves()
{
}


void Moves::PossibleMoves(int pieceID, POINT position, bool color, PieceBag bag)
{
	moves.clear();
	switch (pieceID)
	{
		case 1:
		{
			KingMoves(position, color, bag);
			break;
		}
		case 2:
		{
			QueenMoves(position, color, bag);
			break;
		}
		case 3:
		{
			RookMoves(position, color, bag);
			break;
		}
		case 4:
		{
			BishopMoves(position, color, bag);
			break;
		}
		case 5:
		{
			KnightMoves(position, color, bag);
			break;
		}
		case 6:
		{
			PawnMoves(position, color, bag);
			break;
		}
		default:
		{

		}
	}
}

void Moves::PossibleThreat(int pieceID, POINT position, bool color, PieceBag bag)
{
	moves.clear();
	switch (pieceID)
	{
	case 1:
	{
		KingThreat(position, color, bag);
		break;
	}
	case 2:
	{
		QueenThreat(position, color, bag);
		break;
	}
	case 3:
	{
		RookThreat(position, color, bag);
		break;
	}
	case 4:
	{
		BishopThreat(position, color, bag);
		break;
	}
	case 5:
	{
		KnightThreat(position, color, bag);
		break;
	}
	case 6:
	{
		PawnThreat(position, color, bag);
		break;
	}
	default:
	{
	}
	}
}
void Moves::KingMove(POINT position, bool color, PieceBag bag)
{
	POINT temp;
	if (position.x > 0 && position.y < 7)
	{
		temp.x = position.x - 1;
		temp.y = 7 - (position.y + 1);
		if (!(bag.CheckField({ temp.x, 7 - temp.y }) && bag.current_piece.GetColor() == color))
			moves.push_back(temp);
	}
	if (position.x > 0 && position.y > 0)
	{
		temp.x = position.x - 1;
		temp.y = 7 - (position.y - 1);
		if (!(bag.CheckField({ temp.x, 7 - temp.y }) && bag.current_piece.GetColor() == color))
			moves.push_back(temp);
	}
	if (position.x < 7 && position.y < 7)
	{
		temp.x = position.x + 1;
		temp.y = 7 - (position.y + 1);
		if (!(bag.CheckField({ temp.x, 7 - temp.y }) && bag.current_piece.GetColor() == color))
			moves.push_back(temp);
	}
	if (position.x < 7 && position.y > 0)
	{
		temp.x = position.x + 1;
		temp.y = 7 - (position.y - 1);
		if (!(bag.CheckField({ temp.x, 7 - temp.y }) && bag.current_piece.GetColor() == color))
			moves.push_back(temp);
	}
	if (position.x > 0)
	{
		temp.x = position.x - 1;
		temp.y = 7 - position.y;
		if (!(bag.CheckField({ temp.x, 7 - temp.y }) && bag.current_piece.GetColor() == color))
			moves.push_back(temp);
	}
	if (position.x < 7)
	{
		temp.x = position.x + 1;
		temp.y = 7 - position.y;
		if (!(bag.CheckField({ temp.x, 7 - temp.y }) && bag.current_piece.GetColor() == color))
			moves.push_back(temp);
	}
	if (position.y < 7)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y + 1);
		if (!(bag.CheckField({ temp.x, 7 - temp.y }) && bag.current_piece.GetColor() == color))
			moves.push_back(temp);
	}
	if (position.y > 0)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y - 1);
		if (!(bag.CheckField({ temp.x, 7 - temp.y }) && bag.current_piece.GetColor() == color))
			moves.push_back(temp);
	}
}

void Moves::KingMoves(POINT position, bool color, PieceBag bag)
{
	moves.clear();
	KingMove(position, color, bag);
	CopyVector(king_moves, moves);
	for each (Piece piece in bag.pieces)
	{
		if (piece.GetColor() != color && piece.in_play && piece.GetID())
		{
			if (!king_moves.empty())
			{
				moves.clear();
				PossibleThreat(piece.GetID(), piece.position, piece.GetColor(), bag);
				for each (POINT piece_move in moves)
				{
					for each (POINT king_move in king_moves)
					{
						if (king_move == piece_move)
						{
							king_moves.erase(std::remove(king_moves.begin(), king_moves.end(), king_move), king_moves.end());//ERASE-REMOVE IDIOM
							break;
						}
					}
					if (king_moves.empty()) break;
				}
			}
		}
		if (color && piece.GetVectorID() == 31) break;
		if (!color && piece.GetVectorID() > 15) break;
	}
	CopyVector(moves, king_moves);//Error
}

void Moves::QueenMoves(POINT position, bool color, PieceBag bag)
{
	POINT temp;
	int i = 0;
	for (i = 0; i < position.x && i < (7 - position.y); ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		if (!PushMove(temp, color, bag)) break;
	}
	for (i = 0; i < position.x && i < position.y; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		if (!PushMove(temp, color, bag)) break;
	}
	for (i = 0; i < (7 - position.x) && i < (7 - position.y); ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		if (!PushMove(temp, color, bag)) break;
	}
	for (i = 0; i < (7 - position.x) && i < position.y; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		if (!PushMove(temp, color, bag)) break;
	}
	for (i = 0; i < position.x; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - position.y;
		if (!PushMove(temp, color, bag)) break;
	}
	for (i = 0; i < 7 - position.x; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - position.y;
		if (!PushMove(temp, color, bag)) break;
	}
	for (i = 0; i < position.y; ++i)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y - (i + 1));
		if (!PushMove(temp, color, bag)) break;
	}
	for (i = 0; i < 7 - position.y; ++i)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y + (i + 1));
		if (!PushMove(temp, color, bag)) break;
	}
}

void Moves::RookMoves(POINT position, bool color, PieceBag bag)
{
	POINT temp;
	int i = 0;
	for (i = 0; i < position.x; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - position.y;
		if (!PushMove(temp, color, bag)) break;
		else
			moves.push_back(temp);
	}
	for (i = 0; i < 7 - position.x; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - position.y;
		if (!PushMove(temp, color, bag)) break;
	}
	for (i = 0; i < position.y; ++i)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y - (i + 1));
		if (!PushMove(temp, color, bag)) break;
	}
	for (i = 0; i < 7 - position.y; ++i)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y + (i + 1));
		if (!PushMove(temp, color, bag)) break;
	}
}

void Moves::BishopMoves(POINT position, bool color, PieceBag bag)
{
	POINT temp;
	int i = 0;
	for (i = 0; i < position.x && i < (7 - position.y); ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		if(!PushMove(temp, color, bag)) break;		
	}
	for (i = 0; i < position.x && i < position.y; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		if (!PushMove(temp, color, bag)) break;
	}
	for (i = 0; i < (7 - position.x) && i < (7 - position.y); ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		if (!PushMove(temp, color, bag)) break;
	}
	for (i = 0; i < (7 - position.x) && i < position.y; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		if (!PushMove(temp, color, bag)) break;
	}
}

void Moves::KnightMoves(POINT position, bool color, PieceBag bag)
{
	POINT temp;
	if (position.x > 0 && position.y < 6)
	{
		temp.x = position.x - 1;
		temp.y = 7 - (position.y + 2);
		PushMove(temp, color, bag);
	}
	if (position.x > 0 && position.y > 1)
	{
		temp.x = position.x - 1;
		temp.y = 7 - (position.y - 2);
		PushMove(temp, color, bag);
	}
	if (position.x < 7 && position.y < 6)
	{
		temp.x = position.x + 1;
		temp.y = 7 - (position.y + 2);
		PushMove(temp, color, bag);
	}
	if (position.x < 7 && position.y > 1)
	{
		temp.x = position.x + 1;
		temp.y = 7 - (position.y - 2);
		PushMove(temp, color, bag);
	}
	if (position.x > 1 && position.y < 7)
	{
		temp.x = position.x - 2;
		temp.y = 7 - (position.y + 1);
		PushMove(temp, color, bag);
	}
	if (position.x > 1 && position.y > 0)
	{
		temp.x = position.x - 2;
		temp.y = 7 - (position.y - 1);
		PushMove(temp, color, bag);
	}
	if (position.x < 6 && position.y < 7)
	{
		temp.x = position.x + 2;
		temp.y = 7 - (position.y + 1);
		PushMove(temp, color, bag);
	}
	if (position.x < 6 && position.y > 0)
	{
		temp.x = position.x + 2;
		temp.y = 7 - (position.y - 1);
		PushMove(temp, color, bag);
	}
}

void Moves::PawnMoves(POINT position, bool color, PieceBag bag)
{
	POINT temp;
	POINT curr_p;
	if (color)
	{	
		temp.x = position.x;
		temp.y = 7 - (position.y + 1);
		curr_p = { temp.x, 7 - temp.y };
		if (!bag.CheckField(curr_p))
		{
			moves.push_back(temp);
			if (position.y == 1)
			{
				temp.x = position.x;
				temp.y = 7 - (position.y + 2);
				curr_p = { temp.x, 7 - temp.y };
				if (!bag.CheckField(curr_p))
				{
					moves.push_back(temp);
					en_passant_possible = true;
				}
			}
		}
		if (position.y < 7) 
		{
			if (position.x > 0)
			{
				temp.x = position.x - 1;
				temp.y = 7 - (position.y + 1);
				curr_p = { temp.x, 7 - temp.y };
				if ((bag.CheckField(curr_p) && !bag.current_piece.GetColor()) || 
					(en_passant_color != color && en_passant && en_passant_x.x == curr_p.x && en_passant_x.y == curr_p.y - 1))
					moves.push_back(temp);				
			}
			if (position.x < 7)
			{
				temp.x = position.x + 1;
				temp.y = 7 - (position.y + 1);
				curr_p = { temp.x, 7 - temp.y };
				if ((bag.CheckField(curr_p) && !bag.current_piece.GetColor()) || 
					(en_passant_color != color && en_passant && en_passant_x.x == curr_p.x && en_passant_x.y == curr_p.y - 1))
					moves.push_back(temp);
			}
		}
	}
	if (!color)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y - 1);
		curr_p = { temp.x, 7 - temp.y };
		if (!bag.CheckField(curr_p))
		{
			moves.push_back(temp);
			if (position.y == 6)
			{
				temp.x = position.x;
				temp.y = 7 -  (position.y - 2);
				curr_p = { temp.x, 7 - temp.y };
				if (!bag.CheckField(curr_p))
				{
					moves.push_back(temp);
					en_passant_possible = true;
				}
			}
		}
		if (position.y > 0)
		{
			if (position.x > 0)
			{
				temp.x = position.x - 1;
				temp.y = 7 - (position.y - 1);
				curr_p = { temp.x, 7 - temp.y };
				if (bag.CheckField(curr_p) && bag.current_piece.GetColor() || 
					(en_passant_color != color && en_passant && en_passant_x.x == curr_p.x && en_passant_x.y == curr_p.y + 1))
					moves.push_back(temp);
			}
			if (position.x < 7)
			{
				temp.x = position.x + 1;
				temp.y = 7 - (position.y - 1);
				curr_p = { temp.x, 7 - temp.y };
				if (bag.CheckField(curr_p) && bag.current_piece.GetColor() ||
					(en_passant_color != color && en_passant && en_passant_x.x == curr_p.x && en_passant_x.y == curr_p.y + 1))
					moves.push_back(temp);
			}
		}
	}
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

bool Moves::Check(PieceBag bag, POINT field_position, bool white_turn )
{
	moves.clear();
	if (bag.last_piece.GetID() == 6)
		PawnThreat(field_position, bag.last_piece.GetColor(), bag);
	else 
		PossibleMoves(bag.last_piece.GetID(), field_position, bag.last_piece.GetColor(), bag);
	for each (POINT item in moves)
	{
		if (white_turn && item.x == black_king_position.x && 7 - item.y == black_king_position.y)
			return true;
		else if (!white_turn && item.x == white_king_position.x && 7 - item.y == white_king_position.y)
			return true;
	}
	return false;
}

bool Moves::Under_Check(PieceBag bag, bool white_turn, POINT king_position)
{
	for each(Piece piece in bag.pieces)
	{
		if (piece.GetColor() != white_turn && piece.in_play)
		{
			moves.clear();
			if (piece.GetID() == 1)
				KingThreat(piece.position, piece.GetColor(), bag);
			else if (piece.GetID() == 6)
				PawnThreat(piece.position, piece.GetColor(), bag);
			else 
				PossibleMoves(piece.GetID(), piece.position, piece.GetColor(), bag);
			for each (POINT piece_move in moves)
			{
				if (piece_move.x == king_position.x && 7 - piece_move.y == king_position.y) return true;
			}
		}
		if (white_turn && piece.GetVectorID() == 31) break;
		if (!white_turn && piece.GetVectorID() > 15) break;
	}
	return false;
}

POINT Moves::King_Position(bool color)
{
	if (color) return white_king_position;
	return black_king_position;
}

void Moves::KingThreat(POINT position, bool color, PieceBag bag)
{
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
}

void Moves::QueenThreat(POINT position, bool color, PieceBag bag)
{
	POINT temp;
	int i = 0;
	for (i = 0; i < position.x && i < (7 - position.y); ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		if (!PushThreat(temp, color, bag)) break;
	}
	for (i = 0; i < position.x && i < position.y; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		if (!PushThreat(temp, color, bag)) break;
	}
	for (i = 0; i < (7 - position.x) && i < (7 - position.y); ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		if (!PushThreat(temp, color, bag)) break;
	}
	for (i = 0; i < (7 - position.x) && i < position.y; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		if (!PushThreat(temp, color, bag)) break;
	}
	for (i = 0; i < position.x; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - position.y;
		if (!PushThreat(temp, color, bag)) break;
	}
	for (i = 0; i < 7 - position.x; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - position.y;
		if (!PushThreat(temp, color, bag)) break;
	}
	for (i = 0; i < position.y; ++i)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y - (i + 1));
		if (!PushThreat(temp, color, bag)) break;
	}
	for (i = 0; i < 7 - position.y; ++i)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y + (i + 1));
		if (!PushThreat(temp, color, bag)) break;
	}
}

void Moves::RookThreat(POINT position, bool color, PieceBag bag)
{
	POINT temp;
	int i = 0;
	for (i = 0; i < position.x; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - position.y;
		if (!PushThreat(temp, color, bag)) break;
	}
	for (i = 0; i < 7 - position.x; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - position.y;
		if (!PushThreat(temp, color, bag)) break;
	}
	for (i = 0; i < position.y; ++i)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y - (i + 1));
		if (!PushThreat(temp, color, bag)) break;
	}
	for (i = 0; i < 7 - position.y; ++i)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y + (i + 1));
		if (!PushThreat(temp, color, bag)) break;
	}
}

void Moves::BishopThreat(POINT position, bool color, PieceBag bag)
{
	POINT temp;
	int i = 0;
	for (i = 0; i < position.x && i < (7 - position.y); ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		if (!PushThreat(temp, color, bag)) break;
	}
	for (i = 0; i < position.x && i < position.y; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		if (!PushThreat(temp, color, bag)) break;
	}
	for (i = 0; i < (7 - position.x) && i < (7 - position.y); ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		if (!PushThreat(temp, color, bag)) break;
	}
	for (i = 0; i < (7 - position.x) && i < position.y; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		if (!PushThreat(temp, color, bag)) break;
	}
}

void Moves::KnightThreat(POINT position, bool color, PieceBag bag)
{
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
}

void Moves::PawnThreat(POINT position, bool color, PieceBag bag)
{
	POINT temp;
	if (color)
	{
		if (position.y < 7)
		{
			if (position.x > 0)
			{
				temp.x = position.x - 1;
				temp.y = 7 - (position.y + 1);
				moves.push_back(temp);
			}
			if (position.x < 7)
			{
				temp.x = position.x + 1;
				temp.y = 7 - (position.y + 1);
				moves.push_back(temp);
			}
		}
	}
	if (!color)
	{
		if (position.y > 0)
		{
			if (position.x > 0)
			{
				temp.x = position.x - 1;
				temp.y = 7 - (position.y - 1);
				moves.push_back(temp);
			}
			if (position.x < 7)
			{
				temp.x = position.x + 1;
				temp.y = 7 - (position.y - 1);
				moves.push_back(temp);
			}
		}
	}
}

bool Moves::PushThreat(POINT temp, bool color, PieceBag bag)
{
	if (bag.CheckField({ temp.x, 7 - temp.y }))
	{
		if (bag.current_piece.GetColor() != color && bag.current_piece.GetID() == 1)
			moves.push_back(temp);
		else
		{
			moves.push_back(temp);
			return false;
		}
	}
	else
		moves.push_back(temp);
	return true;
}

bool Moves::PushMove(POINT temp, bool color, PieceBag bag)
{

	if (bag.CheckField({ temp.x, 7 - temp.y }))
	{
		if (bag.current_piece.GetColor() != color)
		{
			moves.push_back(temp);
			return false;
		}
		else return false;
	}
	else
		moves.push_back(temp);
	return true;
}

void Moves::CopyVector(std::vector<POINT> &a, const std::vector<POINT> &b)
{
	a.clear();
	for each (POINT move in b)
	{
		a.push_back(move);
	}
}

bool operator==(const POINT &a, const POINT &b) { return (a.x == b.x && a.y == b.y); }