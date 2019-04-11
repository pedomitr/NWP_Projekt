#pragma once
class General
{
public:
	General();
	~General();
	void InitializeGame(RECT cr);
	void PlayMove(RECT cr);
	void PlacePiece(RECT curr_field, RECT cr, double piece_color, double piece_type);
};


