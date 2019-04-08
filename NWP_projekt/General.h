#pragma once
class General
{
public:
	HWND hWnd = AfxGetApp()->m_pMainWnd->m_hWnd;
	std::string column_name[8] = { "a", "b","c", "d", "e", "f", "g", "h" };
	std::string row_name[8] = { "1", "2", "3", "4", "5", "6", "7", "8" };
	COLORREF white_field = RGB(255, 255, 178);
	COLORREF black_field = RGB(51, 25, 0); 
	COLORREF white_piece = RGB(255, 255, 255);
	COLORREF black_piece = RGB(0, 0, 0);
	bool white_turn = true;
	bool piece_selected = false;
	RECT current_rect = { 0 };
	General();
	~General();
	void InitializeGame(CDC* pDC, RECT cr);
	void PlayMove(CDC* pDC, RECT cr);
	void PlacePiece(CDC* pDC, RECT curr_field, RECT cr, double piece_color, double piece_type);
};


