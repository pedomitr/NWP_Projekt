
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

		//Crtanje figura ///////////////
		CImage pngImage;
		CBitmap pngBmp;
		CDC bmDC;
		CBitmap *pOldbmp;
		BITMAP  bi;

		RECT curr_field = { 6, 6, 7, 7};
		//////////////////////

		//Inicijalizacija figura
		RECT firstField = { 0, 7, 1, 8 };//za referencu
		POINT p = { 0 };
		Figure piece1;
		bool loadedImage = false;	

		SetMapMode(*pDC, MM_ANISOTROPIC);
		SetWindowExtEx(*pDC, 8, 8, 0);

		//White
		for (p.x = 0, p.y = 6; p.x < 8;)
		{
			curr_field = { p.x, p.y, ++p.x, p.y + 1 };
			SetViewportExtEx(*pDC, curr_field.left, curr_field.top, 0);//put this line on clicked point

			if (loadedImage == false) {
				pngImage.Load(pngPath);
				
				pngBmp.Attach(pngImage.Detach());

				bmDC.CreateCompatibleDC(pDC);

				loadedImage = true;
			}
				pOldbmp = bmDC.SelectObject(&pngBmp);
				pngBmp.GetBitmap(&bi);

			//Za prozirnu pozadinu figura
			/*pDC->TransparentBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
				&bmDC, bi.bmWidth * figure1.pawn, bi.bmHeight * figure1.white_piece, bi.bmWidth / 6, bi.bmHeight / 2, (255, 255, 255));*/
			pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
				&bmDC, bi.bmWidth * figure1.pawn, bi.bmHeight * figure1.white_piece, SRCCOPY);
			bmDC.SelectObject(pOldbmp);
		}



		p.x = 0;
		p.y = 7;
		for each (double item in figure)
		{
			curr_field = { p.x, p.y, ++p.x, p.y + 1 };
			SetViewportExtEx(*pDC, curr_field.left, curr_field.top, 0);//put this line on clicked point

			if (loadedImage == false) {
				pngImage.Load(pngPath);

				pngBmp.Attach(pngImage.Detach());

				bmDC.CreateCompatibleDC(pDC);

				loadedImage = true;
			}
			pOldbmp = bmDC.SelectObject(&pngBmp);
			pngBmp.GetBitmap(&bi);

			pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
				&bmDC, bi.bmWidth * item, bi.bmHeight * figure1.white_piece, SRCCOPY);
			bmDC.SelectObject(pOldbmp);

		}

		//Black
		for (p.x = 0, p.y = 1, i = 0; p.x < 8;)
		{
			curr_field = { p.x, p.y, ++p.x , p.y + 1 };
			SetViewportExtEx(*pDC, curr_field.left, curr_field.top, 0);//put this line on clicked point

			if (loadedImage == false) {
				pngImage.Load(pngPath);

				pngBmp.Attach(pngImage.Detach());

				bmDC.CreateCompatibleDC(pDC);

				loadedImage = true;
			}
			pOldbmp = bmDC.SelectObject(&pngBmp);
			pngBmp.GetBitmap(&bi);
			pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
				&bmDC, bi.bmWidth * figure1.pawn, bi.bmHeight * figure1.black_piece, SRCCOPY);
		}

		p.x = 0;
		p.y = 0;
		for each (double item in figure)
		{
			curr_field = { p.x, p.y, ++p.x, p.y + 1 };
			SetViewportExtEx(*pDC, curr_field.left, curr_field.top, 0);//put this line on clicked point

			if (loadedImage == false) {
				pngImage.Load(pngPath);

				pngBmp.Attach(pngImage.Detach());

				bmDC.CreateCompatibleDC(pDC);

				loadedImage = true;
			}
			pOldbmp = bmDC.SelectObject(&pngBmp);
			pngBmp.GetBitmap(&bi);

			pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
				&bmDC, bi.bmWidth * item, bi.bmHeight * figure1.black_piece, SRCCOPY);
		}

		bmDC.SelectObject(pOldbmp);// staviti na kraju crtanja figura
	}

/*
	p.x = 0;
	p.y = 7;
	Rook temp_r = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.rook, bi.bmHeight * figure1.white_piece, SRCCOPY);
	w_piece.push_back(temp_r);

	++p.x;
	Knight temp_n = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.knight, bi.bmHeight * figure1.white_piece, SRCCOPY);
	w_piece.push_back(temp_n);

	++p.x;
	Bishop temp_b = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.bishop, bi.bmHeight * figure1.white_piece, SRCCOPY);
	w_piece.push_back(temp_b);

	++p.x;
	Queen temp_q = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.queen, bi.bmHeight * figure1.white_piece, SRCCOPY);
	w_piece.push_back(temp_q);

	++p.x;
	King temp_k = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.king, bi.bmHeight * figure1.white_piece, SRCCOPY);
	w_piece.push_back(temp_k);

	++p.x;
	temp_b = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.bishop, bi.bmHeight * figure1.white_piece, SRCCOPY);
	w_piece.push_back(temp_b);

	++p.x;
	temp_n = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.knight, bi.bmHeight * figure1.white_piece, SRCCOPY);
	w_piece.push_back(temp_n);

	++p.x;
	temp_r = { p, true, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.rook, bi.bmHeight * figure1.white_piece, SRCCOPY);
	w_piece.push_back(temp_r);

	//Black
	temp_p = { p, false, ++i };
	for (p.x = 0, p.y = 1; p.x < 8; ++i, ++p.x)
	{
		temp_p.position.x = p.x;
		temp_p.pieceID = i;
		curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
		pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
			&bmDC, bi.bmWidth * figure1.pawn, bi.bmHeight * figure1.black_piece, SRCCOPY);
		w_piece.push_back(temp_p);
	}
	p.x = 0;
	p.y = 0;
	temp_r = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.rook, bi.bmHeight * figure1.black_piece, SRCCOPY);
	w_piece.push_back(temp_r);

	++p.x;
	temp_n = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.knight, bi.bmHeight * figure1.black_piece, SRCCOPY);
	w_piece.push_back(temp_n);

	++p.x;
	temp_b = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.bishop, bi.bmHeight * figure1.black_piece, SRCCOPY);
	w_piece.push_back(temp_b);

	++p.x;
	temp_q = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.queen, bi.bmHeight * figure1.black_piece, SRCCOPY);
	w_piece.push_back(temp_q);

	++p.x;
	temp_k = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.king, bi.bmHeight * figure1.black_piece, SRCCOPY);
	w_piece.push_back(temp_k);

	++p.x;
	temp_b = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.bishop, bi.bmHeight * figure1.black_piece, SRCCOPY);
	w_piece.push_back(temp_b);

	++p.x;
	temp_n = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.knight, bi.bmHeight * figure1.black_piece, SRCCOPY);
	w_piece.push_back(temp_n);

	++p.x;
	temp_r = { p, false, ++i };
	curr_field = { p.x, p.y, p.x + 1, p.y + 1 };
	pDC->BitBlt(cr.bottom * 8 / 9, cr.bottom * 8 / 9, bi.bmWidth / 6, bi.bmHeight / 2,
		&bmDC, bi.bmWidth * figure1.rook, bi.bmHeight * figure1.black_piece, SRCCOPY);
	w_piece.push_back(temp_r);


	bmDC.SelectObject(pOldbmp);// staviti na kraju crtanja figura
	*/
	//Kraj Inicijalizacije figura
	//Dodavanje figura na ploču

	//TO DO

	//

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
	/*CClientDC pDC(this);
	RECT cr;
	GetClientRect(&cr);
	SetMapMode(pDC, MM_ANISOTROPIC);
	SetViewportExtEx(pDC, cr.left, cr.top, 0);
	SetWindowExtEx(pDC, 9, 9, 0);*/
	

	//OSTAJE!!!!!!!!!!!!!!!
	RECT cr;
	GetClientRect(&cr);
	int hField = cr.bottom / 9;
	RECT firstField = { 0, 7, 1, 8 };
	Fields* fields = new Fields(firstField, hField);
	POINT field_position = fields->GetFieldPosition(point, fields);
	TCHAR* name = _T("");
	fields->GetFieldName(field_position, name);
	current_field = fields->GetField(field_position, firstField);
	white_turn = !white_turn;
	Invalidate();
	UpdateWindow();
	///////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	//DrawText(pDC, _T("K"), -1, &curr_field, DT_CENTER | DT_SINGLELINE);

	//Figure piece1;
	//game1.PlacePiece(&pDC, game1.current_rect, cr, piece1.white_piece, piece1.pawn);
	//pDC.SetTextColor(game1.black_piece);
	//pDC.SetBkColor(game1.white_piece);
	/*pDC.SetTextColor(game1.black_piece);
	pDC.SetBkColor(RGB(255, 0, 0));
	pDC.ExtTextOutW((int)&curr_field.left, (int)&curr_field.top, ETO_OPAQUE, &curr_field, L"K", 1, 0);*/

	/*CString pngPath = _T("res\\figure.png");
	CImage pngImage;
	CBitmap pngBmp;
	CDC bmDC;
	CBitmap *pOldbmp;
	BITMAP  bi;

	CClientDC dc(this);

	pngImage.Load(pngPath);

	pngBmp.Attach(pngImage.Detach());

	bmDC.CreateCompatibleDC(&dc);

	pOldbmp = bmDC.SelectObject(&pngBmp);
	pngBmp.GetBitmap(&bi);

	dc.BitBlt(cr.bottom * 8 / 9, cr.bottom * 8/ 9, bi.bmWidth / 6, bi.bmHeight / 2, &bmDC, bi.bmWidth * 5/ 6, bi.bmHeight / 2, SRCCOPY);
	bmDC.SelectObject(pOldbmp);*/



	CView::OnLButtonDown(nFlags, point);
}

RECT CompareField(int hField, RECT field) {
	RECT compare_field = { hField * field.left, hField * field.top,  hField * field.right, hField * field.bottom };
	return compare_field;
}




