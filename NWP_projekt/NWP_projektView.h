
#include "Figure.h"
#include "PieceBag.h"
#include "Moves.h"
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
	COLORREF piece_highlight = RGB(153, 115, 89);
	COLORREF dot_trnasparent = RGB(255, 255, 255);
	bool white_turn = true;
	bool m_New_File = false;
	bool m_New_Game = false;
	RECT current_field = { 0 };
	CString pngPath = _T("res\\figure.png");
	CString pngPath_dot = _T("res\\dot.png");
	CString current_field_name = _T("");
	bool m_lb_click1 = false;
	bool m_lb_click2 = false;
	bool m_end_turn = false;
	bool m_check = false;
	bool m_checkmate = false;
	bool m_promotion = false;
	bool m_victory = false;
	bool m_draw = false;
	PieceBag bag;
	Moves moves;
};

#ifndef _DEBUG  // debug version in NWP_projektView.cpp
inline CNWPprojektDoc* CNWPprojektView::GetDocument() const
   { return reinterpret_cast<CNWPprojektDoc*>(m_pDocument); }
#endif

