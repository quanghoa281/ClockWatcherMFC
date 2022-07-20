
// ClockWatcherDlg.h : header file
//

#pragma once

#define PI  3.14;

// CClockWatcherDlg dialog
class CClockWatcherDlg : public CDialogEx
{
// Construction
public:
	CClockWatcherDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLOCKWATCHER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	CBitmap BmBklrClk;
	UINT_PTR ETime;
	UINT_PTR NTime;
	int radiusClk;
public:

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CPoint getPosSec(CPoint center, int secmin);
	CPoint getPosMin(CPoint center, int secmin);
	CPoint getPosHour(CPoint center, int h);

};
