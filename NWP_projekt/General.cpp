#include "stdafx.h"
#include "General.h"
#include "NWP_projekt.h"
#include "NWP_projektDoc.h"
#include "NWP_projektView.h"

#include "Fields.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"

General::General()
{
}


General::~General()
{
}

void General::InitializeGame(CDC* pDC, RECT cr)
{
	white_turn = true;
	HBRUSH brush = CreateSolidBrush(white_field);
	HPEN pen = CreatePen(PS_SOLID, 4, black_field);
	SetMapMode(*pDC, MM_ISOTROPIC);
	SetViewportExtEx(*pDC, cr.right, cr.bottom, 0);
	SetWindowExtEx(*pDC, 10, 10, 0);
	RECT border = { 1, 0, 9, 8 };
	pDC->Rectangle(&border);
	FillRect(*pDC, &border, brush);
	brush = CreateSolidBrush(RGB(51, 25, 0));
	for (int i = 1; i < 9; ++i) {
		for (int j = i & 1; j < 8; j += 2) {
			RECT r = { i, j, i + 1, j + 1 };
			FillRect(*pDC, &r, brush);
		}
	}
	//Dodaj oznake oko ploèe
	TCHAR *letter_marks[] = { _T("     a"), _T("     b"), _T("     c"), _T("     d"),
		_T("     e"), _T("     f"), _T("     g"), _T("     h") };
	TCHAR *number_marks[] = { _T("1"), _T("2"), _T("3"), _T("4"),
	_T("5"), _T("6"), _T("7"), _T("8") };


	RECT markings;
	int i = 1;
	int j = 8;
	SetTextColor(*pDC, black_field);
	SetBkColor(*pDC, white_piece);
	for each (TCHAR  *item in letter_marks)
	{
		markings = { i , j, ++i, j + 1 };
		DrawText(*pDC, item, -1, &markings, DT_CENTER | DT_SINGLELINE);
	}
	i = 9;
	j = 8;
	for each (TCHAR  *item in number_marks)
	{
		markings = { i , --j, i + 1, j + 1 };
		pDC->DrawText(item, -1, &markings, DT_VCENTER | DT_SINGLELINE);
	
	}

	//Postavljanje figura
	TCHAR* figure_symbols_pieces[] = { _T("R"), _T("N"),  _T("B"), _T("Q"),  _T("K"),  _T("B"),  _T("N"),  _T("R") };
	TCHAR* figure_symbols_pawns = _T("P");
	//Bijele
	i = 1;
	j = 7;
	for each (TCHAR  *item in figure_symbols_pieces)
	{
		markings = { i , j, ++i, j + 1 };
		DrawText(*pDC, item, -1, &markings, DT_CENTER | DT_SINGLELINE);
	}

	for (i = 1, j = 6; i < 9;)
	{
		markings = { i , j, ++i, j + 1 };
		DrawText(*pDC, figure_symbols_pawns, -1, &markings, DT_CENTER | DT_SINGLELINE);
	}

	//Crne
	SetTextColor(*pDC, white_piece);
	SetBkColor(*pDC, black_piece);

	i = 1;
	j = 0;
	for each (TCHAR  *item in figure_symbols_pieces)
	{
		markings = { i , j, ++i, j + 1 };
		DrawText(*pDC, item, -1, &markings, DT_CENTER | DT_SINGLELINE);
	}

	for (i = 1, j = 1; i < 9;)
	{
		markings = { i , j, ++i, j + 1 };
		DrawText(*pDC, figure_symbols_pawns, -1, &markings, DT_CENTER | DT_SINGLELINE);

	}

	//Inicijalizacija figura
	RECT firstField = { 1, 7, 2, 8 };//za referencu
	POINT p;
	p.x = 0; p.y = 1;
	std::vector<Piece> w_piece;
	//int i = 0, j = 0;
	//White
	Pawn temp_p = { p, true, 0 };
	for (p.x = 0, p.y = 1, i = 0; p.x < 8; ++i, ++p.x)
	{
		temp_p.position.x = p.x;
		temp_p.pieceID = i;
		w_piece.push_back(temp_p);
	}
	p.x = 0;
	p.y = 0;
	Rook temp_r = { p, true, ++i };
	w_piece.push_back(temp_r);

	++p.x;
	Knight temp_n = { p, true, ++i };
	w_piece.push_back(temp_n);

	++p.x;
	Bishop temp_b = { p, true, ++i };
	w_piece.push_back(temp_n);

	++p.x;
	Queen temp_q = { p, true, ++i };
	w_piece.push_back(temp_q);

	++p.x;
	King temp_k = { p, true, ++i };
	w_piece.push_back(temp_k);

	++p.x;
	temp_b = { p, true, ++i };
	w_piece.push_back(temp_n);

	++p.x;
	temp_n = { p, true, ++i };
	w_piece.push_back(temp_n);

	++p.x;
	temp_r = { p, true, ++i };
	w_piece.push_back(temp_r);

	//Black
	temp_p = { p, false, ++i };
	for (p.x = 0, p.y = 6; p.x < 8; ++i, ++p.x)
	{
		temp_p.position.x = p.x;
		temp_p.pieceID = i;
		w_piece.push_back(temp_p);
	}
	p.x = 0;
	p.y = 7;
	temp_r = { p, false, ++i };
	w_piece.push_back(temp_r);

	++p.x;
	temp_n = { p, false, ++i };
	w_piece.push_back(temp_n);

	++p.x;
	temp_b = { p, false, ++i };
	w_piece.push_back(temp_n);

	++p.x;
	temp_q = { p, false, ++i };
	w_piece.push_back(temp_q);

	++p.x;
	temp_k = { p, false, ++i };
	w_piece.push_back(temp_k);

	++p.x;
	temp_b = { p, false, ++i };
	w_piece.push_back(temp_n);

	++p.x;
	temp_n = { p, false, ++i };
	w_piece.push_back(temp_n);

	++p.x;
	temp_r = { p, false, ++i };
	w_piece.push_back(temp_r);


}

void General::PlayMove(CDC * pDC, RECT cr)
{
	SetMapMode(*pDC, MM_ISOTROPIC);
	SetViewportExtEx(*pDC, cr.right, cr.bottom, 0);
	SetWindowExtEx(*pDC, 10, 10, 0);

	if()
	
}
