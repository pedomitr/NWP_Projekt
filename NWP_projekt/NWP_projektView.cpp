
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

	// Crta ploču za igru
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 178));
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
	//Dodaj oznake oko ploče
	TCHAR *letter_marks[] = { _T("     a"), _T("     b"), _T("     c"), _T("     d"),
		_T("     e"), _T("     f"), _T("     g"), _T("     h") };
	TCHAR *number_marks[] = { _T("1"), _T("2"), _T("3"), _T("4"),
	_T("5"), _T("6"), _T("7"), _T("8") };

	RECT markings;
	int i = 1;
	int j = 8;

	for each (TCHAR  *item in letter_marks)
	{
		markings = { i , j, ++i, j + 1 };
		DrawText(*pDC, item, -1, &markings, DT_CENTER|DT_SINGLELINE);
	}
	i = 9;
	j = 8;
	for each (TCHAR  *item in number_marks)
	{
		markings = { i , --j, i + 1, j + 1};
		pDC->DrawText(item, -1, &markings, DT_VCENTER|DT_SINGLELINE);
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
