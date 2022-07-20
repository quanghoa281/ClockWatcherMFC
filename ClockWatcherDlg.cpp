
// ClockWatcherDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ClockWatcher.h"
#include "ClockWatcherDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClockWatcherDlg dialog



CClockWatcherDlg::CClockWatcherDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLOCKWATCHER_DIALOG, pParent)
{
	ETime = 100;
	NTime = 1000;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClockWatcherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClockWatcherDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CClockWatcherDlg message handlers

BOOL CClockWatcherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetTimer(ETime, NTime, NULL);
	BmBklrClk.LoadBitmap(IDB_BITMAP_CLK);
	CRect crect;
	this->GetClientRect(crect);
	radiusClk = crect.Width() / 2;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClockWatcherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect crect;
		CBitmap* bmObj;
		BITMAP bmClk;
		CDC memDC;
		this->GetClientRect(crect);
		BmBklrClk.GetBitmap(&bmClk);
		memDC.CreateCompatibleDC(&dc);
		bmObj = memDC.SelectObject(&BmBklrClk);
		dc.StretchBlt(0, 0, crect.Width(), crect.Height(), &memDC, 0, 0, bmClk.bmWidth, bmClk.bmHeight, SRCCOPY);

		CTime tnow = CTime::GetCurrentTime();
		int hour = tnow.GetHour();
		int min = tnow.GetMinute();
		int sec = tnow.GetSecond();
		CPoint center;
		center.x = crect.Width() / 2;
		center.y = crect.Height() / 2;

		//hour
		CPen cpen2(PS_SOLID, 10, RGB(0, 0, 0));
		dc.SelectObject(cpen2);
		dc.MoveTo(center);
		CPoint cphour = getPosHour(center, hour * 60 + min);
		dc.LineTo(cphour);
		//minute
		CPen cpen1(PS_SOLID, 7, RGB(0, 0, 0));
		dc.SelectObject(cpen1);
		dc.MoveTo(center);
		CPoint cpmin = getPosMin(center, min);
		dc.LineTo(cpmin);
		//second
		CPen cpen(PS_SOLID, 3, RGB(255, 0, 0));
		dc.SelectObject(cpen);
		dc.MoveTo(center);
		CPoint cpsec = getPosSec(center, sec);
		dc.LineTo(cpsec);

		memDC.SelectObject(bmObj);
		memDC.DeleteDC();

		CDialogEx::OnPaint();

	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClockWatcherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CClockWatcherDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == ETime) {
		Invalidate(true);
	}
	CDialogEx::OnTimer(nIDEvent);
}
CPoint CClockWatcherDlg::getPosSec(CPoint center, int secmin) {
	float twicePi = 2.0f * PI;
	float pointAmount = 60;
	float radiusClk1 = radiusClk - 60;
	float x1 = center.x + (radiusClk1 * sin(secmin * twicePi / pointAmount));
	float y1 = -1 * center.y + (radiusClk1 * cos(secmin * twicePi / pointAmount));
	return CPoint(x1, -1 * y1);
}
CPoint CClockWatcherDlg::getPosMin(CPoint center, int secmin) {
	float twicePi = 2.0f * PI;
	float pointAmount = 60;
	float radiusClk1 = radiusClk - 130;
	float x1 = center.x + (radiusClk1 * sin(secmin * twicePi / pointAmount));
	float y1 = -1 * center.y + (radiusClk1 * cos(secmin * twicePi / pointAmount));
	return CPoint(x1, -1 * y1);
}
CPoint CClockWatcherDlg::getPosHour(CPoint center, int h) {
	float twicePi = 2.0f * PI;
	float pointAmount = 12 * 60;
	float radiusClk1 = radiusClk - 170;
	float x1 = center.x + (radiusClk1 * sin(h * twicePi / pointAmount));
	float y1 = -1 * center.y + (radiusClk1 * cos(h * twicePi / pointAmount));
	return CPoint(x1, -1 * y1);
}
