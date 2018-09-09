
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNWPprojektView

IMPLEMENT_DYNCREATE(CNWPprojektView, CView)

BEGIN_MESSAGE_MAP(CNWPprojektView, CView)
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

	// TODO: add draw code for native data here
	HBRUSH brush = CreateSolidBrush(RGB(255,255,178));
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(51, 25, 0));
	RECT cr;
	GetClientRect(&cr);
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
