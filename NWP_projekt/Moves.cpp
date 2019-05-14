#include "stdafx.h"
#include "Moves.h"
#include <algorithm>

Moves::Moves()
{
}


Moves::~Moves()
{
}



std::vector<POINT> Moves::PossibleMoves(int pieceID, POINT position, bool color, PieceBag bag)
{
	std::vector<POINT> moves;
	switch (pieceID)
	{
		case 1:
		{
			moves = KingMoves(position, color, bag);
			break;
		}
		case 2:
		{
			moves = QueenMoves(position, color, bag);
			break;
		}
		case 3:
		{
			moves = RookMoves(position, color, bag);
			break;
		}
		case 4:
		{
			moves = BishopMoves(position, color, bag);
			break;
		}
		case 5:
		{
			moves = KnightMoves(position, color, bag);
			break;
		}
		case 6:
		{
			moves = PawnMoves(position, color, bag);
			break;
		}
		default:
		{

		}
	}
	return moves;
}


std::vector<POINT> Moves::TheKing(POINT position, bool color, PieceBag bag)
{
	std::vector<POINT> moves;
	POINT temp;
	POINT curr_p;
	if (position.x > 0 && position.y < 7)
	{
		temp.x = position.x - 1;
		temp.y = 7 - (position.y + 1);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p) && bag.current_piece.GetColor() == color)
		{
		}
		else
			moves.push_back(temp);

	}
	if (position.x > 0 && position.y > 0)
	{
		temp.x = position.x - 1;
		temp.y = 7 - (position.y - 1);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p) && bag.current_piece.GetColor() == color)
		{
		}
		else
			moves.push_back(temp);
	}
	if (position.x < 7 && position.y < 7)
	{
		temp.x = position.x + 1;
		temp.y = 7 - (position.y + 1);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p) && bag.current_piece.GetColor() == color)
		{
		}
		else
			moves.push_back(temp);
	}
	if (position.x < 7 && position.y > 0)
	{
		temp.x = position.x + 1;
		temp.y = 7 - (position.y - 1);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p) && bag.current_piece.GetColor() == color)
		{
		}
		else
			moves.push_back(temp);
	}

	if (position.x > 0)
	{
		temp.x = position.x - 1;
		temp.y = 7 - position.y;
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p) && bag.current_piece.GetColor() == color)
		{
		}
		else
			moves.push_back(temp);
	}
	if (position.x < 7)
	{
		temp.x = position.x + 1;
		temp.y = 7 - position.y;
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p) && bag.current_piece.GetColor() == color)
		{
		}
		else
			moves.push_back(temp);
	}
	if (position.y < 7)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y + 1);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p) && bag.current_piece.GetColor() == color)
		{
		}
		else
			moves.push_back(temp);
	}
	if (position.y > 0)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y - 1);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p) && bag.current_piece.GetColor() == color)
		{
		}
		else
			moves.push_back(temp);
	}
	return moves;
}

std::vector<POINT> Moves::PawnThreat(POINT position, bool color, PieceBag bag)
{
	std::vector<POINT> moves;
	POINT temp;
	POINT curr_p;
	if (color)
	{		
		if (position.y < 7)
		{
			if (position.x > 0)
			{
				temp.x = position.x - 1;
				temp.y = 7 - (position.y + 1);
				curr_p = { temp.x, 7 - temp.y };
				moves.push_back(temp);
			}
			if (position.x < 7)
			{
				temp.x = position.x + 1;
				temp.y = 7 - (position.y + 1);
				curr_p = { temp.x, 7 - temp.y };
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
				curr_p = { temp.x, 7 - temp.y };
				moves.push_back(temp);
			}
			if (position.x < 7)
			{
				temp.x = position.x + 1;
				temp.y = 7 - (position.y - 1);
				curr_p = { temp.x, 7 - temp.y };
				moves.push_back(temp);
			}
		}
	}
	return moves;
}


std::vector<POINT> Moves::KingMoves(POINT position, bool color, PieceBag bag)
{
	std::vector<POINT> moves;
	moves = TheKing(position, color, bag);
	//polja pod šahom
	std::vector<POINT> blocked_move;
	for each (Piece piece in bag.pieces)//vrti se beskonacno
	{
		if (piece.GetColor() != color && piece.in_play && piece.GetID())//kralja druge boje provjeriti indirektno
		{
			if (!moves.empty())
			{
				blocked_move.clear();
				if (piece.GetID() == 1) 
				{
					if (color) blocked_move = TheKing(black_king_position, false, bag);
					else blocked_move = TheKing(white_king_position, true, bag);
				}
				else if (piece.GetID() == 6)
				{
					if (color) blocked_move = PawnThreat(piece.position, false, bag);
					else blocked_move = PawnThreat(piece.position, true, bag);
				}
				else blocked_move = PossibleMoves(piece.GetID(), piece.position, piece.GetColor(), bag);
				for each (POINT piece_move in blocked_move)
				{
					for each (POINT king_move in moves)
					{
						if (king_move == piece_move)
						{
							moves.erase(std::remove(moves.begin(), moves.end(), king_move), moves.end());//ERASE-REMOVE IDIOM
							break;
						}
					}
					if (moves.empty()) break;
				}
			}
		}
		//if (color && piece.GetVectorID() == 31) break;
		//if (!color && piece.GetVectorID() > 15) break;
	}
	king_moves.clear();
	for each (POINT king_move in moves)
	{
		king_moves.push_back(king_move);
	}
	return moves;
}

std::vector<POINT> Moves::QueenMoves(POINT position, bool color, PieceBag bag)
{
	std::vector<POINT> moves;
	POINT temp;
	POINT curr_p;
	int i = 0;
	for (i = 0; i < position.x && i < (7 - position.y); ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;		
		}else
			moves.push_back(temp);
	}
	for (i = 0; i < position.x && i < position.y; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	for (i = 0; i < (7 - position.x) && i < (7 - position.y); ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	for (i = 0; i < (7 - position.x) && i < position.y; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	for (i = 0; i < position.x; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - position.y;
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	for (i = 0; i < 7 - position.x; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - position.y;
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	for (i = 0; i < position.y; ++i)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y - (i + 1));
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	for (i = 0; i < 7 - position.y; ++i)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y + (i + 1));
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	return moves;
}

std::vector<POINT> Moves::RookMoves(POINT position, bool color, PieceBag bag)
{
	std::vector<POINT> moves;
	POINT temp;
	POINT curr_p;
	int i = 0;
	for (i = 0; i < position.x; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - position.y;
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	for (i = 0; i < 7 - position.x; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - position.y;
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	for (i = 0; i < position.y; ++i)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y - (i + 1));
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	for (i = 0; i < 7 - position.y; ++i)
	{
		temp.x = position.x;
		temp.y = 7 - (position.y + (i + 1));
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	return moves;
}

std::vector<POINT> Moves::BishopMoves(POINT position, bool color, PieceBag bag)
{
	std::vector<POINT> moves;
	POINT temp;
	POINT curr_p;
	int i = 0;
	for (i = 0; i < position.x && i < (7 - position.y); ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	for (i = 0; i < position.x && i < position.y; ++i)
	{
		temp.x = position.x - (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	for (i = 0; i < (7 - position.x) && i < (7 - position.y); ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y + (i + 1));
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	for (i = 0; i < (7 - position.x) && i < position.y; ++i)
	{
		temp.x = position.x + (i + 1);
		temp.y = 7 - (position.y - (i + 1));
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
				break;
			}
			else break;
		}
		else
			moves.push_back(temp);
	}
	return moves;
}

std::vector<POINT> Moves::KnightMoves(POINT position, bool color, PieceBag bag)
{
	std::vector<POINT> moves;
	POINT temp;
	POINT curr_p;
	if (position.x > 0 && position.y < 6)
	{
		temp.x = position.x - 1;
		temp.y = 7 - (position.y + 2);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
			}
		}
		else
			moves.push_back(temp);
	}
	if (position.x > 0 && position.y > 1)
	{
		temp.x = position.x - 1;
		temp.y = 7 - (position.y - 2);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
			}
		}
		else
			moves.push_back(temp);
	}
	if (position.x < 7 && position.y < 6)
	{
		temp.x = position.x + 1;
		temp.y = 7 - (position.y + 2);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
			}
		}
		else
			moves.push_back(temp);
	}
	if (position.x < 7 && position.y > 1)
	{
		temp.x = position.x + 1;
		temp.y = 7 - (position.y - 2);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
			}
		}
		else
			moves.push_back(temp);
	}
	if (position.x > 1 && position.y < 7)
	{
		temp.x = position.x - 2;
		temp.y = 7 - (position.y + 1);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
			}
		}
		else
			moves.push_back(temp);
	}
	if (position.x > 1 && position.y > 0)
	{
		temp.x = position.x - 2;
		temp.y = 7 - (position.y - 1);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
			}
		}
		else
			moves.push_back(temp);
	}
	if (position.x < 6 && position.y < 7)
	{
		temp.x = position.x + 2;
		temp.y = 7 - (position.y + 1);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
			}
		}
		else
			moves.push_back(temp);
	}
	if (position.x < 6 && position.y > 0)
	{
		temp.x = position.x + 2;
		temp.y = 7 - (position.y - 1);
		curr_p = { temp.x, 7 - temp.y };
		if (bag.CheckField(curr_p))
		{
			if (bag.current_piece.GetColor() != color)
			{
				moves.push_back(temp);
			}
		}
		else
			moves.push_back(temp);
	}
	return moves;
}

std::vector<POINT> Moves::PawnMoves(POINT position, bool color, PieceBag bag)
{
	std::vector<POINT> moves;
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

bool Moves::Check(PieceBag bag, POINT field_position, bool white_turn )
{
	if (bag.current_piece.GetID() == 6)
		moves = PawnThreat(field_position, bag.last_piece.GetColor(), bag);
	else 
		moves = PossibleMoves(bag.last_piece.GetID(), field_position, bag.last_piece.GetColor(), bag);
	for each (POINT item in moves)
	{
		if (white_turn && item.x == black_king_position.x && 7 - item.y == black_king_position.y)
			return true;
		else if (!white_turn && item.x == white_king_position.x && 7 - item.y == white_king_position.y)
			return true;
	}
	return false;
}

bool Moves::Under_Check(PieceBag bag, bool white_turn)
{
	for each(Piece piece in bag.pieces)
	{
		if (piece.GetColor() != white_turn && piece.in_play)
		{
			moves.clear();
			if (piece.GetID() == 1)
			{
				if (white_turn) moves = TheKing(black_king_position, false, bag);
				else moves = TheKing(white_king_position, true, bag);
			}
			else if (piece.GetID() == 6)
			{
				if (white_turn) moves = PawnThreat(piece.position, false, bag);
				else moves = PawnThreat(piece.position, true, bag);
			}
			else moves = PossibleMoves(piece.GetID(), piece.position, piece.GetColor(), bag);

			for each (POINT piece_move in moves)
			{
				if (piece_move.x == white_king_position.x && 7 - piece_move.y == white_king_position.y) return true;
				if (piece_move.x == black_king_position.x && 7 - piece_move.y == black_king_position.y) return true;
			}
		}
		/*if (white_turn && piece.GetVectorID() == 31) break;
		if (!white_turn && piece.GetVectorID() > 15) break;*/
	}
	return false;
}


bool operator==(const POINT &a, const POINT &b) { return (a.x == b.x && a.y == b.y); }