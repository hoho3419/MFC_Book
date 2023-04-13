
// PopupMenuDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "PopupMenu.h"
#include "PopupMenuDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPopupMenuDlg 대화 상자



CPopupMenuDlg::CPopupMenuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POPUPMENU_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPopupMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPopupMenuDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_MY_OPEN, &CPopupMenuDlg::OnMyOpen)
	ON_COMMAND(ID_MY_CLOSE, &CPopupMenuDlg::OnMyClose)
END_MESSAGE_MAP()


// CPopupMenuDlg 메시지 처리기

BOOL CPopupMenuDlg::OnInitDialog()
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

void CPopupMenuDlg::OnPaint()
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
HCURSOR CPopupMenuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPopupMenuDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMenu menu;
	menu.LoadMenu(IDR_MY_MENU);
	CMenu* p_sub_menu = menu.GetSubMenu(0);

	CPoint pos;
	GetCursorPos(&pos);

	p_sub_menu->TrackPopupMenu(TPM_LEFTALIGN, pos.x, pos.y, this);
	menu.DestroyMenu();

	CDialogEx::OnRButtonUp(nFlags, point);
}


void CPopupMenuDlg::OnMyOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(_T("열기가 선택되었습니다"));
}


void CPopupMenuDlg::OnMyClose()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(_T("닫기가 선택되었습니다"));
}
