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
#include "Figure.h"

General::General()
{
}


General::~General()
{
}

void General::InitializeGame(CDC* pDC, RECT cr)
{
	white_turn = true;
	HBRUSH brush = CreateSolidBrush(black_field);
	HPEN pen = CreatePen(PS_SOLID, 4, black_field);
	SetMapMode(*pDC, MM_ISOTROPIC);
	SetWindowExtEx(*pDC, 9, 9, 0);
	SetViewportExtEx(*pDC, cr.right, cr.bottom, 0);
	RECT border = { 0, 0, 8, 8 };
	pDC->Rectangle(&border);
	FillRect(*pDC, &border, brush);
	brush = CreateSolidBrush(white_field);
	for (int i = 0; i < 8; ++i) {
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
	int i = 0;
	int j = 8;
	SetTextColor(*pDC, black_field);
	SetBkColor(*pDC, white_piece);
	for each (TCHAR  *item in letter_marks)
	{
		markings = { i , j, ++i, j + 1 };
		DrawText(*pDC, item, -1, &markings, DT_CENTER | DT_SINGLELINE);
	}
	i = 8;
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
	i = 0;
	j = 7;
	for each (TCHAR  *item in figure_symbols_pieces)
	{
		markings = { i , j, ++i, j + 1 };
		DrawText(*pDC, item, -1, &markings, DT_CENTER | DT_SINGLELINE);
	}

	for (i = 0, j = 6; i < 8;)
	{
		markings = { i , j, ++i, j + 1 };
		DrawText(*pDC, figure_symbols_pawns, -1, &markings, DT_CENTER | DT_SINGLELINE);
	}

	//Crne
	SetTextColor(*pDC, white_piece);
	SetBkColor(*pDC, black_piece);

	i = 0;
	j = 0;
	for each (TCHAR  *item in figure_symbols_pieces)
	{
		markings = { i , j, ++i, j + 1 };
		DrawText(*pDC, item, -1, &markings, DT_CENTER | DT_SINGLELINE);
	}

	for (i = 0, j = 1; i < 8;)
	{
		markings = { i , j, ++i, j + 1 };
		DrawText(*pDC, figure_symbols_pawns, -1, &markings, DT_CENTER | DT_SINGLELINE);

	}

	//Inicijalizacija figura
	RECT firstField = { 0, 7, 1, 8 };//za referencu
	POINT p = { 0 };
	Figure piece1;
	RECT curr_field = { 0 };
	std::vector<Piece> w_piece;
	i = 0, j = 0;
	//White
	Pawn temp_p = { p, true, 0 };
	for (p.x = 0, p.y = 6, i = 0; p.x < 8; ++i, ++p.x)
	{
		temp_p.position.x = p.x;
		temp_p.pieceID = i;
		curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
		PlacePiece(pDC, curr_field, cr, piece1.white_piece, piece1.pawn);
		w_piece.push_back(temp_p);
	}
	p.x = 0;
	p.y = 7;
	Rook temp_r = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.white_piece, piece1.rook);
	w_piece.push_back(temp_r);

	++p.x;
	Knight temp_n = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.white_piece, piece1.knight);
	w_piece.push_back(temp_n);

	++p.x;
	Bishop temp_b = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.white_piece, piece1.bishop);
	w_piece.push_back(temp_b);

	++p.x;
	Queen temp_q = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.white_piece, piece1.queen);
	w_piece.push_back(temp_q);

	++p.x;
	King temp_k = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.white_piece, piece1.king);
	w_piece.push_back(temp_k);

	++p.x;
	temp_b = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.white_piece, piece1.bishop);
	w_piece.push_back(temp_b);

	++p.x;
	temp_n = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.white_piece, piece1.knight);
	w_piece.push_back(temp_n);

	++p.x;
	temp_r = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.white_piece, piece1.rook);
	w_piece.push_back(temp_r);

	//Black
	temp_p = { p, false, ++i };
	for (p.x = 0, p.y = 1; p.x < 8; ++i, ++p.x)
	{
		temp_p.position.x = p.x;
		temp_p.pieceID = i;
		curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
		PlacePiece(pDC, curr_field, cr, piece1.black_piece, piece1.pawn);
		w_piece.push_back(temp_p);
	}
	p.x = 0;
	p.y = 0;
	temp_r = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.black_piece, piece1.rook);
	w_piece.push_back(temp_r);

	++p.x;
	temp_n = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.black_piece, piece1.knight);
	w_piece.push_back(temp_n);

	++p.x;
	temp_b = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.black_piece, piece1.bishop);
	w_piece.push_back(temp_b);

	++p.x;
	temp_q = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.black_piece, piece1.queen);
	w_piece.push_back(temp_q);

	++p.x;
	temp_k = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.black_piece, piece1.king);
	w_piece.push_back(temp_k);

	++p.x;
	temp_b = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.black_piece, piece1.bishop);
	w_piece.push_back(temp_b);

	++p.x;
	temp_n = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.black_piece, piece1.knight);
	w_piece.push_back(temp_n);

	++p.x;
	temp_r = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	PlacePiece(pDC, curr_field, cr, piece1.black_piece, piece1.rook);
	w_piece.push_back(temp_r);
	//Kraj Inicijalizacije figura
}

void General::PlayMove(CDC * pDC, RECT cr)
{
	//
		//TO DO
	//
	
}

void General::PlacePiece(CDC* pDC, RECT curr_field, RECT cr, double piece_color, double piece_type)
{

	/*SIZE s;
	s.cx = cr.bottom * 8 / 9;
	s.cy = s.cx;*/
	//SetViewportOrgEx(*pDC, cr.left - 1, cr.top - 1, 0);
	SetMapMode(*pDC, MM_ANISOTROPIC);
	SetViewportExtEx(*pDC, curr_field.left, curr_field.top, 0);//put this line on clicked point
	SetWindowExtEx(*pDC, 8, 8, 0);
	
	CString pngPath = _T("res\\figure.png");
	CImage pngImage;
	CBitmap pngBmp;
	CDC bmDC;
	CBitmap *pOldbmp;
	BITMAP  bi;

	//CClientDC* dc(pDC);

	pngImage.Load(pngPath);

	pngBmp.Attach(pngImage.Detach());

	bmDC.CreateCompatibleDC(pDC);

	pOldbmp = bmDC.SelectObject(&pngBmp);
	pngBmp.GetBitmap(&bi);

	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8/ 9, bi.bmWidth / 6, bi.bmHeight / 2,
				&bmDC, bi.bmWidth * piece_type, bi.bmHeight * piece_color, SRCCOPY);
	bmDC.SelectObject(pOldbmp);
}
