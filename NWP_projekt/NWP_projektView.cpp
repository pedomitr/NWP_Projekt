
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
	if (m_lb_click2)
	{
		CImage pngImage;
		pngImage.Load(pngPath);

		pngImage.TransparentBlt(*pDC, p_move_to.x, 7 - p_move_to.y, 1, 1,
			pngImage.GetWidth() * figure1.GetByID(bag.current_piece.GetID()), pngImage.GetHeight() * figure1.GetColor(bag.current_piece.GetColor()),
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
	bag.Initialize();

	m_New_File = true;
	Invalidate();
	UpdateWindow();
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
		//white_turn = !white_turn;// kad prođe m_lb_click2
		//Provjeri da li je kliknuta figura i koja 
		if (!m_lb_click1) {
			if (bag.CheckField(field_position) && bag.current_piece.GetColor() == white_turn)
			{
				p_moves.moves = p_moves.PossibleMoves(bag.current_piece.GetID(), bag.current_piece.position, bag.current_piece.GetColor());
				m_lb_click1 = true;
			}
			else m_lb_click1 = false;
		}
		else
		{
			for each (POINT item in p_moves.moves)
			{
				if (field_position.x == item.x && field_position.y == item.y)
				{
					p_move_to = field_position;
					m_lb_click1 = false;
					m_lb_click2 = true;
				}
			}
		}
	}

	Invalidate();
	UpdateWindow();

	CView::OnLButtonDown(nFlags, point);
}

RECT CompareField(int hField, RECT field) {
	return { hField * field.left, hField * field.top,  hField * field.right, hField * field.bottom };
}




