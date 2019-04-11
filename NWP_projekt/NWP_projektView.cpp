
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
		CBitmap pngBmp;
		CDC bmDC;
		CBitmap *pOldbmp;
		BITMAP  bi;
		Figure piece1;
		bool loadedImage = false;	


		//White
		int x = 0, y = 6;
		for (x = 0; x < 8; ++x)
		{
			if (loadedImage == false) {
				pngImage.Load(pngPath);

				pngBmp.Attach(pngImage.Detach());

				bmDC.CreateCompatibleDC(pDC);

				loadedImage = true;
			}

			pOldbmp = bmDC.SelectObject(&pngBmp);
			pngBmp.GetBitmap(&bi);

			pDC->StretchBlt(x, y, 1, 1, &bmDC,
				bi.bmWidth * figure1.pawn, bi.bmHeight * figure1.white_piece,
				bi.bmWidth / 6, bi.bmHeight / 2, SRCCOPY);
		}
			
		x = 0, y = 7;
		for each (double item in figure)
		{
			if (loadedImage == false) {
				pngImage.Load(pngPath);

				pngBmp.Attach(pngImage.Detach());

				bmDC.CreateCompatibleDC(pDC);

				loadedImage = true;
			}
			pOldbmp = bmDC.SelectObject(&pngBmp);
			pngBmp.GetBitmap(&bi);

			pDC->StretchBlt(x, y, 1, 1, &bmDC,
				bi.bmWidth * item, bi.bmHeight * figure1.white_piece,
				bi.bmWidth / 6, bi.bmHeight / 2, SRCCOPY);
			++x;
		}

		//Black
		for (x = 0, y = 1; x < 8; ++x)
		{		
			if (loadedImage == false) {
				pngImage.Load(pngPath);

				pngBmp.Attach(pngImage.Detach());

				bmDC.CreateCompatibleDC(pDC);

				loadedImage = true;
			}
			pOldbmp = bmDC.SelectObject(&pngBmp);
			pngBmp.GetBitmap(&bi);
			pDC->StretchBlt(x, y, 1, 1, &bmDC,
				bi.bmWidth * figure1.pawn, bi.bmHeight * figure1.black_piece,
				bi.bmWidth / 6, bi.bmHeight / 2, SRCCOPY);
		}

		x = 0, y = 0;
		for each (double item in figure)
		{
			if (loadedImage == false) {
				pngImage.Load(pngPath);

				pngBmp.Attach(pngImage.Detach());

				bmDC.CreateCompatibleDC(pDC);

				loadedImage = true;
			}
			pOldbmp = bmDC.SelectObject(&pngBmp);
			pngBmp.GetBitmap(&bi);

			pDC->StretchBlt(x, y, 1, 1, &bmDC,
				bi.bmWidth * item, bi.bmHeight * figure1.black_piece,
				bi.bmWidth / 6, bi.bmHeight / 2, SRCCOPY);
			++x;
		}

		bmDC.SelectObject(pOldbmp);
	}
	//Kraj crtanja figura

	//OnClick

	if (m_lb_click1) 
	{
		CImage pngImage;
		CBitmap pngBmp;
		CDC bmDC;
		CBitmap *pOldbmp;
		BITMAP  bi;
		Figure piece1;
		bool loadedImage = false;

		if (loadedImage == false) {
			pngImage.Load(pngPath);

			pngBmp.Attach(pngImage.Detach());

			bmDC.CreateCompatibleDC(pDC);

			loadedImage = true;
		}

		pOldbmp = bmDC.SelectObject(&pngBmp);
		pngBmp.GetBitmap(&bi);

		pDC->StretchBlt(current_field.left, current_field.top, 1, 1, &bmDC,
			bi.bmWidth * figure1.pawn, bi.bmHeight * figure1.white_piece,
			bi.bmWidth / 6, bi.bmHeight / 2, SRCCOPY);

		bmDC.SelectObject(pOldbmp);
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
}


int CNWPprojektView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{

	return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CNWPprojektView::OnLButtonDown(UINT nFlags, CPoint point)
{
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
		white_turn = !white_turn;
		m_lb_click1 = true;
	}

	Invalidate();
	UpdateWindow();

	CView::OnLButtonDown(nFlags, point);
}

RECT CompareField(int hField, RECT field) {
	RECT compare_field = { hField * field.left, hField * field.top,  hField * field.right, hField * field.bottom };
	return compare_field;
}




