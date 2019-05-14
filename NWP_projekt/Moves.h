#pragma once
#include "Piecebag.h"
class Moves
{
	std::vector<POINT> PossibleThreat(int pieceID, POINT position, bool color, PieceBag bag);
	std::vector<POINT> KingMoves(POINT position, bool color, PieceBag bag);
	std::vector<POINT> QueenMoves(POINT position, bool color, PieceBag bag);
	std::vector<POINT> RookMoves(POINT position, bool color, PieceBag bag);
	std::vector<POINT> BishopMoves(POINT position, bool color, PieceBag bag);
	std::vector<POINT> KnightMoves(POINT position, bool color, PieceBag bag);
	std::vector<POINT> PawnMoves(POINT position, bool color, PieceBag bag);
	std::vector<POINT> KingThreat(POINT position, bool color, PieceBag bag);
	std::vector<POINT> QueenThreat(POINT position, bool color, PieceBag bag);
	std::vector<POINT> RookThreat(POINT position, bool color, PieceBag bag);
	std::vector<POINT> BishopThreat(POINT position, bool color, PieceBag bag);
	std::vector<POINT> KnightThreat(POINT position, bool color, PieceBag bag);
	std::vector<POINT> PawnThreat(POINT position, bool color, PieceBag bag);
	
public:
	bool en_passant = false;
	int en_passant_ID = 0;
	POINT en_passant_x = { 0, 0 };
	bool en_passant_color = true;
	bool en_passant_possible = false;
	POINT white_king_position = { 4, 0 };
	POINT black_king_position = { 4, 7 };	
	Moves();
	~Moves();
	std::vector<POINT> moves;
	std::vector<POINT> king_moves;
	std::vector<POINT> PossibleMoves(int pieceID, POINT position, bool color, PieceBag bag);
	bool GetFieldColor(POINT p_field);
	bool Check(PieceBag bag, POINT field_position, bool white_turn);
	bool Moves::Under_Check(PieceBag bag, bool white_turn, POINT king_position);
	POINT King_Position(bool color);
	friend bool operator==(const POINT &a, const POINT &b);
};

