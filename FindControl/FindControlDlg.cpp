
// FindControlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "FindControl.h"
#include "FindControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFindControlDlg 대화 상자



CFindControlDlg::CFindControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FINDCONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFindControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFindControlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEST_BTN, &CFindControlDlg::OnBnClickedTestBtn)
END_MESSAGE_MAP()


// CFindControlDlg 메시지 처리기

BOOL CFindControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFindControlDlg::OnPaint()
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
HCURSOR CFindControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFindControlDlg::OnBnClickedTestBtn()
{
	/*
	// 찾은 컨트롤의 컨트롤을 찾고 다음 컨트롤 을 찾으려고 함
	HWND f_find_wnd = NULL;
	// 현재 윈도우 안에 있는 특정 컨트롤을 가져오기 m_hWnd(윈도우 핸들값) NULL(시작점,처음부터 찾기),edit(찾을 컨트롤 찾기 대소문자 구분 안함) NULL(그냥 찾겠다)
	while (f_find_wnd = ::FindWindowEx(m_hWnd, f_find_wnd, _T("edit"), NULL))
	{
		::SetWindowText(f_find_wnd, _T("HELLO"));
	}*/
	// MFC 방법
	HWND f_find_wnd = NULL;
	CWnd* p_find_wnd = NULL;
	p_find_wnd = FindWindowEx(m_hWnd, NULL, _T("edit"), NULL);
	while (p_find_wnd != NULL)
	{
		p_find_wnd->SetWindowText(_T("HELLO"));
		p_find_wnd = FindWindowEx(m_hWnd, p_find_wnd->m_hWnd, _T("edit"), NULL);
	}

}
