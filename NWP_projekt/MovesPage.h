#pragma once


// MovesPage dialog

class MovesPage : public CDialogEx
{
	DECLARE_DYNAMIC(MovesPage)

public:
	MovesPage(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MovesPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
