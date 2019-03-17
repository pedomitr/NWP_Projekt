
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
	SetMapMode(pDC, MM_ANISOTROPIC);
	SetWindowExtEx(pDC, 9, 9, 0);
	SetViewportExtEx(pDC, cr.left, cr.top, 0);
	int hField = cr.bottom / 9;
	RECT firstField = { 0, 7, 1, 8 };

	//bool white_turn;
	//bool black_turn;


	Fields* fields = new Fields(firstField, hField);
	POINT field_position = fields->GetFieldPosition(point, fields);
	TCHAR* name = _T("");
	fields->GetFieldName(field_position, name);
	RECT curr_field = fields->GetField(field_position, firstField);
	

	General game1;
	game1.PlacePiece(&pDC, curr_field, cr);
	//pDC.SetTextColor(game1.black_piece);
	//pDC.SetBkColor(game1.white_piece);
	//DrawText(pDC, _T("K"), -1, &curr_field, DT_CENTER | DT_SINGLELINE);
	/*pDC.SetTextColor(game1.black_piece);
	pDC.SetBkColor(RGB(255, 0, 0));
	pDC.ExtTextOutW((int)&curr_field.left, (int)&curr_field.top, ETO_OPAQUE, &curr_field, L"K", 1, 0);*/



	CView::OnLButtonDown(nFlags, point);
}

RECT CompareField(int hField, RECT field) {
	RECT compare_field = { hField * field.left, hField * field.top,  hField * field.right, hField * field.bottom };
	return compare_field;
}




