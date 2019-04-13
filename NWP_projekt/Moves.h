#pragma once
class Moves
{
	std::vector<POINT> KingMoves(POINT position);
	std::vector<POINT> QueenMoves(POINT position);
	std::vector<POINT> RookMoves(POINT position);
	std::vector<POINT> BishopMoves(POINT position);
	std::vector<POINT> KnightMoves(POINT position);
	std::vector<POINT> PawnMoves(POINT position, bool color);
public:
	Moves();
	~Moves();
	std::vector<POINT>moves;
	std::vector<POINT> PossibleMoves(int pieceID, POINT position, bool color);
};

