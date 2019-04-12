
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
#include "Pawn.h"
#include "Figure.h"
#include "General.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
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


	if (m_New_File) 
	{
		RECT cr;
		GetClientRect(&cr);
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

		//Crtanje figura
		CImage pngImage;
		pngImage.Load(pngPath);

		//White
		int x = 0, y = 6;
		for (x = 0; x < 8; ++x)
		{
			pngImage.TransparentBlt(*pDC, x, y, 1, 1,
				pngImage.GetWidth() * figure1.pawn, pngImage.GetHeight() * figure1.white_piece,
				pngImage.GetWidth() / 6, pngImage.GetHeight() / 2, figure1.transparent);
		}
			
		x = 0, y = 7;
		for each (double item in figure)
		{
			pngImage.TransparentBlt(*pDC, x, y, 1, 1,
				pngImage.GetWidth() * item, pngImage.GetHeight() * figure1.white_piece,
				pngImage.GetWidth() / 6, pngImage.GetHeight() / 2, figure1.transparent);
			++x;
		}

		//Black
		for (x = 0, y = 1; x < 8; ++x)
		{		
			pngImage.TransparentBlt(*pDC, x, y, 1, 1,
				pngImage.GetWidth() * figure1.pawn, pngImage.GetHeight() * figure1.black_piece,
				pngImage.GetWidth() / 6, pngImage.GetHeight() / 2, figure1.transparent);
		}

		x = 0, y = 0;
		for each (double item in figure)
		{
			pngImage.TransparentBlt(*pDC, x, y, 1, 1,
				pngImage.GetWidth() * item, pngImage.GetHeight() * figure1.black_piece,
				pngImage.GetWidth() / 6, pngImage.GetHeight() / 2, figure1.transparent);
			++x;
		}
	}
	//Kraj crtanja figura

	//OnClick

	if (m_lb_click1) 
	{
		CImage pngImage;
		pngImage.Load(pngPath);

		pngImage.TransparentBlt(*pDC, current_field.left, current_field.top, 1, 1,
			pngImage.GetWidth() * figure1.pawn, pngImage.GetHeight() * figure1.black_piece,
			pngImage.GetWidth() / 6, pngImage.GetHeight() / 2, figure1.transparent);
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
	m_New_File = true;
	Invalidate();
	UpdateWindow();
	PieceBag bag;
	
	POINT p = { 0,0 };
	int i = 0;
	//White
	for (p.y = 1; i < 8; ++i)
	{
		Pawn temp_p = { {p.x++, p.y}, true, i };
		bag.pieces.push_back(temp_p);
	}
	p.x = 0;
	p.y = 0;
	Rook temp_r = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_r);
	Knight temp_n = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_n);
	Bishop temp_b = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_b);
	Queen temp_q = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_q);
	King temp_k = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_k);
	temp_b = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_b);
	temp_n = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_n);
	temp_r = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_r);

	//Black
	for (p.x = 0, p.y = 6; i < 24; ++i)
	{
		Pawn temp_p = { {p.x++, p.y}, false, i };
		bag.pieces.push_back(temp_p);
	}
	p.x = 0;
	p.y = 7;
	temp_r = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_r);
	temp_n = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_n);
	temp_b = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_b);
	temp_q = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_q);
	temp_k = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_k);
	temp_b = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_b);
	temp_n = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_n);
	temp_r = { {p.x++, p.y}, true, i++ };
	bag.pieces.push_back(temp_r);
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
	PieceBag bag;
	if (field_position.x == 8 || field_position.y == 8) return;
	else
	{
		current_field = fields->GetField(field_position, firstField);
		current_field_name = fields->GetFieldName(field_position);
		//white_turn = !white_turn;// kad prođe m_lb_click2
		//Provjeri da li je kliknuta figura i koja 
		if (bag.CheckField(field_position) && bag.current_piece.color == white_turn)
		{
			bag.current_piece.PossibleMoves();//Stvi novi flag  On draw iscrtava moguće poteze
		}
		m_lb_click1 = true;
	}

	Invalidate();
	UpdateWindow();

	CView::OnLButtonDown(nFlags, point);
}

RECT CompareField(int hField, RECT field) {
	return { hField * field.left, hField * field.top,  hField * field.right, hField * field.bottom };
}




