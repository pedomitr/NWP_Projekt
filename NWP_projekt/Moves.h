#pragma once
#include "Piecebag.h"
class Moves
{
	std::vector<POINT> KingMoves(POINT position, bool color, PieceBag* bag);
	std::vector<POINT> QueenMoves(POINT position, bool color, PieceBag* bag);
	std::vector<POINT> RookMoves(POINT position, bool color, PieceBag* bag);
	std::vector<POINT> BishopMoves(POINT position, bool color, PieceBag* bag);
	std::vector<POINT> KnightMoves(POINT position, bool color, PieceBag* bag);
	std::vector<POINT> PawnMoves(POINT position, bool color, PieceBag* bag);
public:
	Moves();
	~Moves();
	std::vector<POINT>moves;
	std::vector<POINT> PossibleMoves(int pieceID, POINT position, bool color, PieceBag* bag);
	bool GetFieldColor(POINT p_field);
};

