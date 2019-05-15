#pragma once
#include "Piecebag.h"
class Moves
{
	void PossibleThreat(int pieceID, POINT position, bool color, PieceBag bag);
	void KingMove(POINT position, bool color, PieceBag bag);
	void KingMoves(POINT position, bool color, PieceBag bag);
	void QueenMoves(POINT position, bool color, PieceBag bag);
	void RookMoves(POINT position, bool color, PieceBag bag);
	void BishopMoves(POINT position, bool color, PieceBag bag);
	void KnightMoves(POINT position, bool color, PieceBag bag);
	void PawnMoves(POINT position, bool color, PieceBag bag);
	void KingThreat(POINT position, bool color, PieceBag bag);
	void QueenThreat(POINT position, bool color, PieceBag bag);
	void RookThreat(POINT position, bool color, PieceBag bag);
	void BishopThreat(POINT position, bool color, PieceBag bag);
	void KnightThreat(POINT position, bool color, PieceBag bag);
	void PawnThreat(POINT position, bool color, PieceBag bag);
	bool PushThreat(POINT position, bool color, PieceBag bag);
	bool PushMove(POINT temp, bool color, PieceBag bag);
	void CopyVector(std::vector<POINT> &a, const std::vector<POINT> &b);
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
	void PossibleMoves(int pieceID, POINT position, bool color, PieceBag bag);
	bool GetFieldColor(POINT p_field);
	bool Check(PieceBag bag, POINT field_position, bool white_turn);
	bool Moves::Under_Check(PieceBag bag, bool white_turn, POINT king_position);
	POINT King_Position(bool color);
	friend bool operator==(const POINT &a, const POINT &b);
};

