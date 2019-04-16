
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
#include "General.h"
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

		//Crtanje figura
		CImage pngImage;
		pngImage.Load(pngPath);

		for each (Piece item in bag.pieces)
		{
			pngImage.TransparentBlt(*pDC, item.position.x, 7 - item.position.y, 1, 1,
				pngImage.GetWidth() * figure1.GetByID(item.GetID()), pngImage.GetHeight() * figure1.GetColor(item.GetColor()),
				pngImage.GetWidth() / 6, pngImage.GetHeight() / 2, figure1.transparent);
		}

	}

	//OnClick

	if (m_lb_click1)
	{
		SetWindowExtEx(*pDC, 81, 81, 0);
		RECT frame = { current_field.left * 9, current_field.top * 9, current_field.right * 9, current_field.bottom * 9 };
		CBrush brush(piece_highlight);
		pDC->FrameRect(&frame, &brush);
		CImage pngImage;
		pngImage.Load(pngPath_dot);
		for each (POINT item in p_moves.moves)
		{
			SetWindowExtEx(*pDC, 9, 9, 0);
			pngImage.TransparentBlt(*pDC, item.x, item.y, 1, 1, dot_trnasparent);
		}
	}

	/*if (m_lb_click2)
	{
		COLORREF f_color;
		if (p_moves.GetFieldColor(bag.current_piece.position)) f_color = white_field;
		else f_color = black_field;
		HBRUSH brush = CreateSolidBrush(f_color);
		RECT r = { bag.current_piece.position.x, 7 - bag.current_piece.position.y, bag.current_piece.position.x + 1, (7 - bag.current_piece.position.y) + 1 };
		FillRect(*pDC, &r, brush);

		if (p_moves.GetFieldColor(p_move_to)) f_color = white_field;
		else f_color = black_field;
		brush = CreateSolidBrush(f_color);
		r = { p_move_to.x, 7 - p_move_to.y, p_move_to.x + 1, (7 - p_move_to.y) + 1 };
		FillRect(*pDC, &r, brush);
	}*/
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
	m_lb_click1 = false;
	m_lb_click2 = false;
	m_end_turn = false;
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
	if (!m_New_File) return;
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
		if (m_end_turn) 
		{
			m_lb_click2 = false;
			m_end_turn = false;
			white_turn = !white_turn;
			
		}
		if(!m_lb_click2 && m_lb_click1)
		{ 			
			if (bag.CheckField(field_position) == true  && bag.current_piece.GetColor() == white_turn) {
				m_lb_click1 = false;
			}else
			{
				for each (POINT item in p_moves.moves)
				{
					if (field_position.x == item.x && field_position.y == 7 - item.y)
					{
						m_lb_click1 = false;
						bag.current_piece = bag.last_piece;
						bag.pieces.at(bag.current_piece.GetVectorID()).position = field_position;
						m_lb_click2 = true;
						m_end_turn = true;
						break;
					}
				}
			}
		}

		//Provjera da li je kliknuta figura i koja 
		if (!m_lb_click2) {
			if (bag.CheckField(field_position) && bag.current_piece.GetColor() == white_turn)
			{
				bag.last_piece = bag.current_piece;
				p_moves.moves = p_moves.PossibleMoves(bag.current_piece.GetID(), bag.current_piece.position, bag.current_piece.GetColor());
				m_lb_click1 = true;
			}else m_lb_click1 = false;
		}
	}
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}




