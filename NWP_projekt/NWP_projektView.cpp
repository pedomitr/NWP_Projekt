
// NWP_projektView.cpp : implementation of the CNWPprojektView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "NWP_projekt.h"
#endif

#include "NWP_projektDoc.h"
#include "NWP_projektView.h"

#include "Fields.h"
#include "Figure.h"
#include "PieceBag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNWPprojektView

IMPLEMENT_DYNCREATE(CNWPprojektView, CView)

BEGIN_MESSAGE_MAP(CNWPprojektView, CView)
	ON_COMMAND(ID_FILE_NEW, &CNWPprojektView::OnFileNew)
	ON_WM_MOUSEACTIVATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CNWPprojektView construction/destruction

CNWPprojektView::CNWPprojektView() noexcept
{
	// TODO: add construction code here

}

CNWPprojektView::~CNWPprojektView()
{
}

BOOL CNWPprojektView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CNWPprojektView drawing

void CNWPprojektView::OnDraw(CDC* pDC)
{
	CNWPprojektDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (m_New_Game)
	{
		RECT cr;
		GetClientRect(&cr);
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
		//Dodaj oznake oko ploce
		SetWindowExtEx(*pDC, 81, 81, 0);
		TCHAR *letter_marks[] = { _T("a"), _T("b"), _T("c"), _T("d"), _T("e"), _T("f"), _T("g"), _T("h") };
		TCHAR *number_marks[] = { _T("1"), _T("2"), _T("3"), _T("4"), _T("5"), _T("6"), _T("7"), _T("8") };

		RECT markings;
		int i = 0;
		int j = 8;
		SetTextColor(*pDC, black_field);
		SetBkColor(*pDC, white_piece);
		for each (TCHAR  *item in letter_marks)
		{
			markings = { 9 * i , 9 * j, 9 * ++i, 9 * (j + 1) };
			pDC->DrawText(item, -1, &markings, DT_CENTER | DT_SINGLELINE);
		}
		i = 8;
		j = 8;
		for each (TCHAR  *item in number_marks)
		{
			markings = { 9 * i , 9 * --j, 9 * (i + 1), 9 * (j + 1) };
			pDC->DrawText(item, -1, &markings, DT_VCENTER | DT_SINGLELINE);

		}
		//Promote pawn
		if (m_promotion)
		{
			CImage pngImage;
			pngImage.Load(pngPath);
			RECT frame;
			HBRUSH brush_f = CreateSolidBrush(piece_highlight);
			if (white_turn)
			{
				SetWindowExtEx(*pDC, 81, 81, 0);
				frame = { current_field.left * 9, (current_field.top + 1) * 9, current_field.right * 9, (current_field.bottom + 4) * 9 };
				FillRect(*pDC, &frame, brush_f);
				SetWindowExtEx(*pDC, 9, 9, 0);
				for (int i = 1; i < 5; ++i)
				{
					pngImage.TransparentBlt(*pDC, bag.last_piece.position.x, 7 - (bag.last_piece.position.y - i), 1, 1,
						pngImage.GetWidth() * figure1.GetByID(bag.last_piece.GetID() - i), pngImage.GetHeight() * figure1.GetColor(bag.last_piece.GetColor()),
						pngImage.GetWidth() / 6, pngImage.GetHeight() / 2, figure1.transparent);
				}
			}
			else
			{
				SetWindowExtEx(*pDC, 81, 81, 0);
				frame = { current_field.left * 9, (current_field.top - 4) * 9, current_field.right * 9, (current_field.bottom - 1) * 9 };
				FillRect(*pDC, &frame, brush_f);
				SetWindowExtEx(*pDC, 9, 9, 0);
				for (int i = 1; i < 5; ++i)
				{
					pngImage.TransparentBlt(*pDC, bag.last_piece.position.x, 7 - (bag.last_piece.position.y + i), 1, 1,
						pngImage.GetWidth() * figure1.GetByID(bag.last_piece.GetID() - i), pngImage.GetHeight() * figure1.GetColor(bag.last_piece.GetColor()),
						pngImage.GetWidth() / 6, pngImage.GetHeight() / 2, figure1.transparent);
				}
			}
		}
		//Crtanje figura
		CImage pngImage;
		pngImage.Load(pngPath);
		SetWindowExtEx(*pDC, 9, 9, 0);
		for each (Piece item in bag.pieces)
		{
			if (item.in_play)
			{
				pngImage.TransparentBlt(*pDC, item.position.x, 7 - item.position.y, 1, 1,
					pngImage.GetWidth() * figure1.GetByID(item.GetID()), pngImage.GetHeight() * figure1.GetColor(item.GetColor()),
					pngImage.GetWidth() / 6, pngImage.GetHeight() / 2, figure1.transparent);
			}		
		}
		//Highlight
		if (m_lb_click1)
		{
			SetWindowExtEx(*pDC, 81, 81, 0);
			RECT frame = { current_field.left * 9, current_field.top * 9, current_field.right * 9, current_field.bottom * 9 };
			CBrush brush(piece_highlight);
			pDC->FrameRect(&frame, &brush);
			CImage pngImage;
			pngImage.Load(pngPath_dot);
			for each (POINT item in moves.moves)
			{
				SetWindowExtEx(*pDC, 9, 9, 0);
				pngImage.TransparentBlt(*pDC, item.x, item.y, 1, 1, dot_trnasparent);
			}
		}
		//Endscreen
		if ((m_checkmate || m_draw)  && !m_victory )
		{
			SetWindowExtEx(*pDC, 9, 9, 0);
			RECT victory_box = { 0, 3, 8, 5 };
			RECT cr;
			GetClientRect(&cr);
			HPEN pen = CreatePen(PS_SOLID, 4, black_field);
			HBRUSH brush = CreateSolidBrush(piece_highlight);
			CFont font;
			font.CreatePointFont(cr.bottom, _T("Arial"), pDC);
			CFont* pOldFont = pDC->SelectObject(&font);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(piece_highlight);
			wchar_t s[128];
			if (m_draw)
			{
				LoadString(GetModuleHandle(NULL),IDS_STRING_1 , s, sizeof(s));
				//LoadStringByReference()
				pDC->DrawText( s, &victory_box, DT_CENTER | DT_VCENTER);
			}
			else if (white_turn)
			{
				LoadString(GetModuleHandle(NULL), IDS_STRING_2, s, sizeof(s));
				pDC->DrawText(s, &victory_box, DT_CENTER | DT_VCENTER);
			}
			else
			{
				LoadString(GetModuleHandle(NULL), IDS_STRING_3, s, sizeof(s));
				pDC->DrawText(s, &victory_box, DT_CENTER | DT_VCENTER);
			}
			m_victory = true;
			pDC->SelectObject(pOldFont);
		}
	}
}


// CNWPprojektView diagnostics

#ifdef _DEBUG
void CNWPprojektView::AssertValid() const
{
	CView::AssertValid();
}

void CNWPprojektView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNWPprojektDoc* CNWPprojektView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNWPprojektDoc)));
	return (CNWPprojektDoc*)m_pDocument;
}
#endif //_DEBUG


// CNWPprojektView message handlers


void CNWPprojektView::OnFileNew()
{	
	bag.Initialize();
	moves.move_repeat = 0;
	moves.last_white_ID = 32;
	moves.last_black_ID = 32;
	moves.white_play = { 8,8 };
	moves.black_play = { 8,8 };
	m_victory = false;
	m_checkmate = false;
	m_draw = false;
	m_lb_click1 = false;
	m_lb_click2 = false;
	m_end_turn = false;
	white_turn = true;
	m_New_File = true;
	m_New_Game = true;

	Invalidate();
}


int CNWPprojektView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{

	return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CNWPprojektView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_victory) Invalidate();
	if (!m_New_File || m_checkmate || m_draw) return;
	RECT cr;
	GetClientRect(&cr);
	int hField = cr.bottom / 9;
	RECT firstField = { 0, 7, 1, 8 };
	Fields* fields = new Fields(firstField, hField);
	POINT field_position = fields->GetFieldPosition(point, fields);
	if (field_position.x == 8 || field_position.y == 8) return;
	else
	{
		current_field = fields->GetField(field_position, firstField);
		current_field_name = fields->GetFieldName(field_position);
		//Promocija pijuna u odabranu figuru
		if (m_promotion)
		{
			if (white_turn && field_position.x == bag.last_piece.position.x && field_position.y < bag.last_piece.position.y &&
				field_position.y > bag.last_piece.position.y - 5)
				bag.Promote((bag.last_piece.position.y - field_position.y), &bag);
			else if (field_position.x == bag.last_piece.position.x && field_position.y > bag.last_piece.position.y &&
					field_position.y < bag.last_piece.position.y + 5)
					bag.Promote((field_position.y - bag.last_piece.position.y), &bag);
			else
				return;
			m_check = moves.Check(bag, bag.last_piece.position, white_turn);
			//Provjera da li je zadan šah-mat
			if (m_check) m_checkmate = moves.Checkmate(white_turn, bag);
			//Provjera da li je izjednačeno
			if (!m_checkmate)
				m_draw = (moves.InsufficinetMaterial(white_turn, bag) ||
					moves.Stalemate(white_turn, bag) ||
					moves.ThreeFoldRepetition(white_turn, field_position, bag));
			m_promotion = false;
		}
		else
		{
			if (m_end_turn)
			{
				m_lb_click2 = false;
				m_end_turn = false;
				white_turn = !white_turn;
			}
			//Drugi klik
			if (!m_lb_click2 && m_lb_click1)
			{
				if (bag.CheckField(field_position) && bag.current_piece.GetColor() == white_turn) {
					m_lb_click1 = false;
				}
				else
				{
					for each (POINT item in moves.moves)
					{
						if (field_position.x == item.x && field_position.y == 7 - item.y)
						{
							m_lb_click1 = false;
							//Ako je figura pojedena
							if (bag.current_piece.GetColor() != bag.last_piece.GetColor())
							{
								bag.pieces.at(bag.current_piece.GetVectorID()).in_play = false;
								bag.pieces.at(bag.last_piece.GetVectorID()).position = field_position;
								if (moves.Under_Check(bag, white_turn, moves.King_Position(white_turn)))
								{
									bag.pieces.at(bag.last_piece.GetVectorID()).position = bag.last_piece.position;
									bag.pieces.at(bag.current_piece.GetVectorID()).in_play = true;
									m_lb_click1 = false;
									m_lb_click2 = false;
									m_end_turn = false;
									break;
								}
							}
							//Ako je En passant uzet
							else if (bag.last_piece.GetID() == 6 && moves.en_passant && moves.en_passant_color != white_turn &&
								bag.last_piece.position.y == moves.en_passant_x.y && field_position.x == moves.en_passant_x.x &&
								((bag.last_piece.GetColor() && field_position.y == moves.en_passant_x.y + 1) ||
								(!bag.last_piece.GetColor() && field_position.y == moves.en_passant_x.y - 1)))
								 {
									bag.pieces.at(moves.en_passant_ID).in_play = false;
									bag.pieces.at(bag.last_piece.GetVectorID()).position = field_position;
									if (moves.Under_Check(bag, white_turn, moves.King_Position(white_turn)))
									{
										bag.pieces.at(bag.last_piece.GetVectorID()).position = bag.last_piece.position;
										bag.pieces.at(moves.en_passant_ID).in_play = true;
										m_lb_click1 = false;
										m_lb_click2 = false;
										m_end_turn = false;
										break;
									}
									moves.en_passant = false;
								 }
							else
							{
								//Ako je šah poslije poteza poništi potez
								bag.pieces.at(bag.last_piece.GetVectorID()).position = field_position;
								if (moves.Under_Check(bag, white_turn, moves.King_Position(white_turn)))
								{
									bag.pieces.at(bag.last_piece.GetVectorID()).position = bag.last_piece.position;
									m_lb_click1 = false;
									m_lb_click2 = false;
									m_end_turn = false;
									break;
								}
							}														
							//Zapamti novu poziciju kralja
							if (bag.last_piece.GetID() == 1)
							{
								if (white_turn) moves.white_king_position = field_position;
								else moves.black_king_position = field_position;
							}
							//Provjera da li je zadan šah
							m_check = moves.Under_Check(bag, !white_turn, moves.King_Position(!white_turn));
							//Provjera da li je zadan šah-mat
							if (m_check) m_checkmate = moves.Checkmate(white_turn, bag);
							//Provjera da li je izjednačeno
							if (!m_checkmate)
								m_draw = (moves.InsufficinetMaterial(white_turn, bag) ||
								moves.Stalemate(white_turn, bag) ||
								moves.ThreeFoldRepetition(white_turn, field_position, bag));
							//Provjera za En passant
							if (bag.last_piece.GetID() == 6 && moves.en_passant_possible)
							{
								if (white_turn && field_position.y == 3)
								{
									moves.en_passant_x = field_position;
									moves.en_passant_color = bag.last_piece.GetColor();
									moves.en_passant_ID = bag.last_piece.GetVectorID();
									moves.en_passant = true;
								}
								else if (!white_turn && field_position.y == 4)
								{
									moves.en_passant_x = field_position;
									moves.en_passant_color = bag.last_piece.GetColor();
									moves.en_passant_ID = bag.last_piece.GetVectorID();
									moves.en_passant = true;
								}
								else moves.en_passant = false;
							}
							else moves.en_passant_possible = false;
							//Provjera za promociju pijuna
							if (bag.last_piece.GetID() == 6)
							{
								if (white_turn && field_position.y == 7)
									m_promotion = true;
								else if (field_position.y == 0)
									m_promotion = true;
							}
							//Provjera za rokadu
							if (bag.last_piece.GetID() == 3)
							{
								POINT x = { 0,0 };
								if (white_turn)
								{
									if(moves.white_king_big_castle && field_position == x)
										moves.white_king_big_castle = false;
									x = { 7, 0 };
									if (moves.white_king_small_castle && field_position == x)
										moves.white_king_small_castle = false;
								}				
								else
								{
									x = { 0, 7 };
									if (moves.black_king_big_castle && field_position == x )
										moves.black_king_big_castle = false;
									x = { 7,7 };
									if (moves.black_king_small_castle && field_position == x)
										moves.black_king_small_castle = false;
								}
							}
							if (bag.last_piece.GetID() == 1)
							{
								POINT x = { 2, 0 };
								if (white_turn)
								{
									if (moves.big_castle_possible && field_position == x)
									{
										x = { 0,0 };
										bag.CheckField(x);
										bag.pieces.at(bag.current_piece.GetVectorID()).position = { 3, 0 };
										moves.white_king_big_castle = false;
										moves.white_king_small_castle = false;
										moves.big_castle_possible = false;
										moves.small_castle_possible = false;
									}
									x = { 6, 0 };
									if (moves.small_castle_possible && field_position == x)
									{
										x = { 7,0 };
										bag.CheckField(x);
										bag.pieces.at(bag.current_piece.GetVectorID()).position = { 5, 0 };
										moves.white_king_big_castle = false;
										moves.white_king_small_castle = false;
										moves.big_castle_possible = false;
										moves.small_castle_possible = false;
									}
									x = { 2,0 };
									if ((moves.white_king_big_castle && !(field_position == x)))
										moves.white_king_big_castle = false;
									x = { 6, 0 };
									if((moves.white_king_small_castle && !(field_position == x)))
										moves.white_king_small_castle = false;
								}
								else
								{
									x = {2, 7};
									if (moves.big_castle_possible && field_position == x)
									{
										x = { 0,7 };
										bag.CheckField(x);
										bag.pieces.at(bag.current_piece.GetVectorID()).position = { 3, 7 };
										moves.black_king_big_castle = false;
										moves.black_king_small_castle = false;
										moves.big_castle_possible = false;
										moves.small_castle_possible = false;
									}
									x = { 6, 7 };
									if (moves.small_castle_possible && field_position == x)
									{
										x = { 7,7 };
										bag.CheckField(x);
										bag.pieces.at(bag.current_piece.GetVectorID()).position = { 5, 7 };
										moves.black_king_big_castle = false;
										moves.black_king_small_castle = false;
										moves.big_castle_possible = false;
										moves.small_castle_possible = false;
									}
									x = { 2, 7 };
									if ((moves.black_king_big_castle && !(field_position == x)))
										moves.black_king_big_castle = false;
									x = { 6, 7 };
									if ((moves.black_king_small_castle && !(field_position == x)))
										moves.black_king_small_castle = false;
								}								
							}							
							bag.last_piece.position = field_position;
							m_lb_click2 = true;
							m_end_turn = true;
							break;
						}
					}
				}
			}
			//Prvi klik
			//Provjera da li je kliknuta figura i koja 
			if (!m_lb_click2) {
				if (bag.CheckField(field_position) && bag.current_piece.GetColor() == white_turn && bag.current_piece.in_play)
				{
					bag.last_piece = bag.current_piece;
					moves.PossibleMoves(bag.current_piece.GetID(), bag.current_piece.position, bag.current_piece.GetColor(), bag);
					m_lb_click1 = true;
				}
				else m_lb_click1 = false;
			}
		}
	}
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}

