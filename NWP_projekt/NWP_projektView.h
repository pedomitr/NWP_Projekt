
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
};

#ifndef _DEBUG  // debug version in NWP_projektView.cpp
inline CNWPprojektDoc* CNWPprojektView::GetDocument() const
   { return reinterpret_cast<CNWPprojektDoc*>(m_pDocument); }
#endif

