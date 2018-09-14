
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

	//Klikanje

	
	//Dodavanje figura na ploču
	/*markings = { 1,1, 8, 8 };

	CImage image;
	image.Load(_T("figure.png"));
	image.Draw( *pDC, markings);*/
	/*
	{
		CString pngPath = _T("C:\\Users\\domit\\source\repos\\NWP\\NWP_projekt\\NWP_projekt\\resnormal_chess_set_symbols_igor_k_01");
		CPngImage pngImage;
		CBitmap pngBmp;
		CDC bmDC;
		CBitmap *pOldbmp;
		BITMAP bi;
		UINT xPos = 450, yPos = 300;

		CClientDC dc(this);

		pngImage.Load(pngPath);
		pngBmp.Attach(pngImage.Detach());
		bmDC.CreateCompatibleDC(&dc);

		pOldbmp = bmDC.SelectObject(&pngBmp);
		pngBmp.GetBitmap(&bi);

		dc.BitBlt(xPos, yPos, bi.bmWidth, bi.bmHeight, &bmDC, 0, 0, SRCCOPY);
		bmDC.SelectObject(pOldbmp);
	}
	*/



	/*HANDLE hBitmap = ::LoadImage(0, _T("chess_set.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CBitmap bitmap;
	bitmap.Attach((HBITMAP)hBitmap);*/

	/*HINSTANCE hInst = AfxGetResourceHandle();
	HBITMAP hBitmap;
	hBitmap = (HBITMAP)::LoadImage(NULL, _T("C:\\Users\domit\source\repos\NWP\NWP_projekt\NWP_projekt\resfigurines.png"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HDC hLocalDC;
	hLocalDC = ::CreateCompatibleDC(*pDC);

	BITMAP qBitmap;
	int iResult = GetObject(hBitmap, sizeof(BITMAP), &qBitmap);

	HBITMAP holdBmp = (HBITMAP)::SelectObject(hLocalDC, hBitmap);

	BOOL qRetBlit = ::BitBlt(*pDC, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight,
		hLocalDC, 0, 0, SRCCOPY);

	::SelectObject(hLocalDC, holdBmp);
	::DeleteDC(hLocalDC);
	::DeleteObject(hBitmap);*/



	


	/*	int nWidth = 75;
		int nHeight = 75;
		int nTargetWidth = 457;

		int m_nSection = 6;
		int nCoordX = m_nSection * 75;
		int nCoordY = 0;

		CBitmap* pOldTargetBmp = NULL;
		CBitmap* pOldSourceBmp = NULL;
		CDC targetDC;
		CDC sourceDC;

		targetDC.CreateCompatibleDC(pDC);
		sourceDC.CreateCompatibleDC(pDC);

		////pOldTargetBmp = targetDC.SelectObject(&m_BmpTarget);
		////pOldSourceBmp = sourceDC.SelectObject(pBmpSource);

		targetDC.BitBlt(nCoordX, nCoordY, nTargetWidth, nHeight, &sourceDC, 0, 0, SRCCOPY);

		sourceDC.SelectObject(pOldSourceBmp);
		targetDC.SelectObject(pOldTargetBmp);

		targetDC.DeleteDC();
		targetDC.DeleteDC();

		//ReleaseDC(pDC); 

		////m_ctrlTargetImage.SetBitmap(HBITMAP(m_BmpTarget));

	//Bitmapa
	CBitmap m_bitmap;
	tagBITMAP m_bm = {0, 800, 204, 32, 32, 32};
	m_bitmap.LoadBitmapW(_T("figure.png"));
	m_bitmap.GetObject(sizeof(BITMAP), &m_bm);

	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	dcMem.SelectObject(m_bitmap);

	pDC->StretchBlt(5, 5, cr.right, cr.bottom, 
		//&dcMem, 0, 0, 800, 204, SRCCOPY);
		&dcMem, 0, 0, m_bm.bmWidth - 1, m_bm.bmHeight - 1, SRCCOPY);*/

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

	// Crta ploču za igru
	CDC* pDC = GetDC();
	RECT cr;
	GetClientRect(&cr);
	General game1;
	game1.InitializeGame(pDC, cr);	
}


int CNWPprojektView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{

	return CView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CNWPprojektView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC pDC(this);
	RECT cr;
	GetClientRect(&cr);
	SetMapMode(pDC, MM_ISOTROPIC);
	SetViewportExtEx(pDC, cr.right, cr.bottom, 0);
	SetWindowExtEx(pDC, 10, 10, 0);
	int hField = cr.bottom / 10;
	RECT firstField = { 1, 7, 2, 8 };

	bool white_turn;
	bool black_turn;


	Fields* fields = new Fields(firstField, hField);
	POINT field_position = fields->GetFieldPosition(point, fields);
	TCHAR* name = fields->GetFieldName(field_position);
	RECT curr_field = fields->GetField(field_position, firstField);

	DrawText(pDC, _T("K"), -1, &curr_field, DT_CENTER | DT_SINGLELINE);

	CView::OnLButtonDown(nFlags, point);
}

RECT CompareField(int hField, RECT field) {
	RECT compare_field = { hField * field.left, hField * field.top,  hField * field.right, hField * field.bottom };
	return compare_field;
}

