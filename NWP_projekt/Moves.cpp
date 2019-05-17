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
	if ((white_king_big_castle && color) || (black_king_big_castle && !color))
	{
		temp = King_Position(color);
		if (!bag.CheckField({ temp.x - 1 , temp.y }) && !bag.CheckField({ temp.x - 2 , temp.y }) && !bag.CheckField({ temp.x - 3 , temp.y }) &&
			bag.CheckField({ temp.x - 4 , temp.y }) && bag.current_piece.GetID() == 3)
		{
			moves.push_back({ temp.x - 2, 7 - temp.y });
			big_castle_possible = true;
		}
	}
	if ((white_king_small_castle && color) || (black_king_small_castle && !color))
	{
		temp = King_Position(color);
		if (!bag.CheckField({ temp.x + 1 , temp.y }) && !bag.CheckField({ temp.x + 2 , temp.y }) &&
			bag.CheckField({ temp.x + 3, temp.y }) && bag.current_piece.GetID() == 3)
		{
			moves.push_back({ temp.x + 2 , 7 - temp.y });
			small_castle_possible = true;
		}
	}
}

void Moves::KingMoves(POINT position, bool color, PieceBag bag)
{
	moves.clear();
	KingMove(position, color, bag);
	CopyVector(king_moves, moves);
	for each (Piece piece in bag.pieces)
	{
		if (king_moves.empty()) break;
		if (piece.GetColor() != color && piece.in_play)
		{
			moves.clear();
			PossibleThreat(piece.GetID(), piece.position, piece.GetColor(), bag);
			for each (POINT piece_move in moves)
			{
				for each (POINT king_move in king_moves)
				{
					if (king_move == piece_move)
					{
						king_moves.erase(std::remove(king_moves.begin(), king_moves.end(), king_move), king_moves.end());
						break;
					}
				}
			}
		}
		if (color && piece.GetVectorID() == 31) break;
		if (!color && piece.GetVectorID() > 15) break;
	}
	CopyVector(moves, king_moves);
}

void Moves::QueenMoves(POINT position, bool color, PieceBag bag)
{
	RookMoves(position, color, bag);
	BishopMoves(position, color, bag);
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
	POINT king_position = King_Position(!white_turn);
	moves.clear();
	if (bag.last_piece.GetID() == 6)
		PawnThreat(field_position, bag.last_piece.GetColor(), bag);
	else 
		PossibleMoves(bag.last_piece.GetID(), field_position, bag.last_piece.GetColor(), bag);
	for each (POINT item in moves)
	{
		if(item.x == king_position.x && 7 - item.y == king_position.y)
			return true;
	}
	return false;
}

bool Moves::Under_Check(PieceBag bag, bool white_turn, POINT king_position)
{
	if (bag.last_piece.GetID() == 1)
		king_position = bag.pieces.at(bag.last_piece.GetVectorID()).position;
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
				if (piece_move.x == king_position.x && 7 - piece_move.y == king_position.y)
				{
					check_ID.push_back(piece.GetVectorID());
					return true;
				}
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
	RookThreat(position, color, bag);
	BishopThreat(position, color, bag);
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

bool Moves::Checkmate(bool color, PieceBag bag)
{
	KingMoves(King_Position(!color), !color, bag);
	if (!king_moves.empty())
		return false;
	std::vector<int> temp_v;
	CopyVector(temp_v, check_ID);
	if (check_ID.size() > 1) return true;
	for each(int i in check_ID)
	{
		Piece temp_p = bag.pieces.at(i);
		PossibleMoves(temp_p.GetID(), temp_p.position, temp_p.GetColor(), bag);
		if (Under_Check(bag, temp_p.GetColor(), temp_p.position)) return false;
		for each(POINT move in moves)
		{
			if (Under_Check(bag, temp_p.GetColor(), { move.x, 7 - move.y }))
				return false;
		}
	}	
	return true;
}

bool Moves::InsufficinetMaterial(bool color, PieceBag bag)
{
	int in_play = 0;
	std::vector<int> remaining_white;
	std::vector<int> remaining_black;
	for each(Piece piece in bag.pieces)
	{
		if (piece.in_play)
		{
			++in_play;
			if (piece.GetID() != 1)
			{
				if (piece.GetColor())
					remaining_white.push_back(piece.GetID());
				else
					remaining_black.push_back(piece.GetID());
			}
		}
	}
	if (in_play == 2)
		return true;
	if (in_play == 3)
	{
		if (remaining_white.empty())
		{
			for each(int b in remaining_black)
			{
				if (b == 4 || b == 5)
					return true;
			}
		}
		if (remaining_black.empty())
		{
			for each(int w in remaining_white)
			{
				if (w == 4 || w == 5)
					return true;
			}
		}
	}
	if (in_play == 4)
	{
		for each(int w in remaining_white)
		{
			for each(int b in remaining_black)
			{
				if ((w == 4 || w == 5) && (b == 4 || b == 5))
					return true;
			}
		}
	}
	return false;
}

bool Moves::Stalemate(bool color, PieceBag bag)
{
	for each(Piece piece in bag.pieces)
	{
		if (piece.in_play)
		{
			if (piece.GetColor() != color)
			{
				PossibleMoves(piece.GetID(), piece.position, piece.GetColor(), bag);
				if (!moves.empty())
					return false;
			}
		}
	}
	return true;
}

bool Moves::ThreeFoldRepetition(bool color, POINT field_position, PieceBag bag)
{
	if (color)
	{
		if (white_play == field_position && last_white_ID == bag.last_piece.GetVectorID())
			++move_repeat;			
		else
			move_repeat = 2;
		white_play = bag.last_piece.position;
		last_white_ID = bag.last_piece.GetVectorID();
	}
	else 
	{
		if (black_play == field_position && last_black_ID == bag.last_piece.GetVectorID())
			++move_repeat;
		else
			move_repeat = 2;
		black_play = bag.last_piece.position;
		last_black_ID = bag.last_piece.GetVectorID();
	}
	if (move_repeat == 8)
		return true;
	return false;
}

void Moves::CopyVector(std::vector<POINT> &a, const std::vector<POINT> &b)
{
	a.clear();
	for each (POINT move in b)
	{
		a.push_back(move);
	}
}

void Moves::CopyVector(std::vector<int> &a, const std::vector<int> &b)
{
	a.clear();
	for each (int ID in b)
	{
		a.push_back(ID);
	}
}

bool operator==(const POINT &a, const POINT &b) { return (a.x == b.x && a.y == b.y); }