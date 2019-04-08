
#include "Figure.h"
// NWP_projektView.h : interface of the CNWPprojektView class
//

#pragma once


class CNWPprojektView : public CView
{
protected: // create from serialization only
	CNWPprojektView() noexcept;
	DECLARE_DYNCREATE(CNWPprojektView)

// Attributes
public:
	CNWPprojektDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CNWPprojektView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileNew();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	Figure figure1;
	std::string column_name[8] = { "a", "b","c", "d", "e", "f", "g", "h" };
	std::string row_name[8] = { "1", "2", "3", "4", "5", "6", "7", "8" };
	double figure[8] = { figure1.rook, figure1.knight, figure1.bishop, figure1.queen, figure1.king, figure1.bishop,  figure1.knight, figure1.rook };
	COLORREF white_field = RGB(255, 255, 178);
	COLORREF black_field = RGB(51, 25, 0);
	COLORREF white_piece = RGB(255, 255, 255);
	COLORREF black_piece = RGB(0, 0, 0);
	bool white_turn = true;
	bool piece_selected = false;
	bool m_New_File = false;
	RECT current_field = { 0 };
	CString pngPath = _T("res\\figure.png");
};

#ifndef _DEBUG  // debug version in NWP_projektView.cpp
inline CNWPprojektDoc* CNWPprojektView::GetDocument() const
   { return reinterpret_cast<CNWPprojektDoc*>(m_pDocument); }
#endif

