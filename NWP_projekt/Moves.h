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
	void CopyVector(std::vector<int> &a, const std::vector<int> &b);
public:
	bool en_passant = false;
	int en_passant_ID = 0;
	POINT en_passant_x = { 0, 0 };
	bool en_passant_color = true;
	bool en_passant_possible = false;
	POINT white_king_position = { 4, 0 };
	POINT black_king_position = { 4, 7 };	
	bool white_king_big_castle = true;
	bool white_king_small_castle = true;
	bool black_king_big_castle = true;
	bool black_king_small_castle = true;
	bool big_castle_possible = false;
	bool small_castle_possible = false;
	bool rook_check = false;
	std::vector<int> check_ID;
	Moves();
	~Moves();
	int move_repeat = 0;
	int last_white_ID;
	int last_black_ID;
	POINT white_play = { 8,8 };
	POINT black_play = { 8,8 };
	std::vector<POINT> unmate_moves;
	std::vector<POINT> moves;
	std::vector<POINT> king_moves;
	std::vector<POINT> check_moves;
	bool checked = false;
	void PossibleMoves(int pieceID, POINT position, bool color, PieceBag bag);
	bool GetFieldColor(POINT p_field);
	bool Check(PieceBag bag, POINT field_position, bool white_turn);
	bool Moves::Under_Check(PieceBag* bag, bool white_turn, POINT king_position);
	bool Moves::Blockable_Check(PieceBag* bag, bool white_turn, POINT piece_position);
	bool Checkmate(bool color, PieceBag *bag);
	bool InsufficinetMaterial(bool color, PieceBag bag);
	bool Stalemate(bool color, PieceBag bag);
	bool ThreeFoldRepetition(bool color, POINT field_position, PieceBag bag);
	POINT King_Position(bool color);
	friend bool operator==(const POINT &a, const POINT &b);
};

