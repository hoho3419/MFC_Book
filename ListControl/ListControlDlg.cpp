
// ListControlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ListControl.h"
#include "ListControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CListControlDlg 대화 상자



CListControlDlg::CListControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LISTCONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_view1);
	DDX_Control(pDX, IDC_LIST2, m_list_view2);
}

BEGIN_MESSAGE_MAP(CListControlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CListControlDlg 메시지 처리기

BOOL CListControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_list_view1.InsertColumn(1, _T("결과값"), LVCFMT_CENTER, 150, 1);
	m_list_view1.InsertColumn(2, _T("날짜"), LVCFMT_CENTER, 100, 2);
	m_list_view1.InsertColumn(3, _T("시간"), LVCFMT_CENTER, 100, 3);

	m_list_view1.InsertItem(1, _T("3131"), 0);
	m_list_view1.InsertItem(1, _T("헬로"), 1);
	/*
	m_list_view1.InsertItem(1, _T("하이"), 2);
	*/
	m_list_view1.SetItemText(0, 1, _T("안녕"));
	m_list_view1.SetItemText(0, 2, _T("Hi"));
	m_list_view1.SetItemText(1, 1, _T("안녕하세요"));
	m_list_view1.SetItemText(1, 2, _T("HELLO"));

	m_list_view1.SetExtendedStyle(m_list_view1.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_TRACKSELECT);
	m_list_view1.SetExtendedStyle(m_list_view1.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	LV_COLUMN col1;
	col1.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col1.fmt = LVCFMT_CENTER;
	m_list_view2.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	wchar_t* result[3] = {_T("결과값"),_T("날짜"), _T("시간")};
	int wid[3] = { 100,200,100 };
	for (int i = 0; i < 3; i++)
	{
		col1.pszText = result[i];
		col1.iSubItem = i;
		col1.cx = wid[i];
		m_list_view2.InsertColumn(i, &col1);
	}
	m_list_view2.SetExtendedStyle(m_list_view2.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_list_view2.InsertItem(1, _T("3131"), 0);
	//m_list_view2.SetItemText(0, 0, _T("안녕"));
	m_list_view2.SetItemText(0, 1, _T("2022년 3월 3일"));
	m_list_view2.SetItemText(0, 2, _T("1시 35분"));
	// LVITEM
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CListControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CListControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

