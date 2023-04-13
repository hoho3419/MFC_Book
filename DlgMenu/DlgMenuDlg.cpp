
// DlgMenuDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "DlgMenu.h"
#include "DlgMenuDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDlgMenuDlg 대화 상자



CDlgMenuDlg::CDlgMenuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLGMENU_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgMenuDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CDlgMenuDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CDlgMenuDlg::OnBnClickedStopBtn)
	ON_COMMAND(ID_START_CMD, &CDlgMenuDlg::OnStartCmd)
	ON_COMMAND(ID_EDIT_CLEAR_CMD, &CDlgMenuDlg::OnEditClearCmd)
END_MESSAGE_MAP()


// CDlgMenuDlg 메시지 처리기

BOOL CDlgMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_STATE_EDIT, _T("멈췄습니다."));
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	GetMenu()->GetSubMenu(0)->EnableMenuItem(IDC_STOP_BTN, MF_BYCOMMAND | MF_DISABLED);
	// 악셀레이터 단축기 등록 
	m_acc_key = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MY_ACC));
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDlgMenuDlg::OnPaint()
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
HCURSOR CDlgMenuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDlgMenuDlg::OnBnClickedStartBtn()
{
	m_start_flag = 1;
	SetDlgItemText(IDC_STATE_EDIT, _T("시작했습니다"));
	GetDlgItem(IDC_START_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(TRUE);
	UpdateMenu();
}

void CDlgMenuDlg::UpdateMenu()
{
	CMenu* p_menu = GetMenu();
	if (p_menu != NULL) {
		CMenu* p_sub_menu = p_menu->GetSubMenu(0);
		if (p_sub_menu != NULL) {
			if (m_start_flag) {
				// 시작 상태이면 시작 메뉴를 비활성화 시키고 멈춤 메뉴를 활성화시킨다.
				p_sub_menu->EnableMenuItem(ID_START_CMD, MF_BYCOMMAND | MF_DISABLED);
				p_sub_menu->EnableMenuItem(IDC_STOP_BTN, MF_BYCOMMAND | MF_ENABLED);
			}
			else {
				p_sub_menu->EnableMenuItem(ID_START_CMD, MF_BYCOMMAND | MF_ENABLED);
				p_sub_menu->EnableMenuItem(IDC_STOP_BTN, MF_BYCOMMAND | MF_DISABLED);
			}
		}
		
	}
}

void CDlgMenuDlg::OnBnClickedStopBtn()
{
	m_start_flag = 0;
	SetDlgItemText(IDC_STATE_EDIT, _T("멈췄습니다."));
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	UpdateMenu();
}


void CDlgMenuDlg::OnStartCmd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnBnClickedStartBtn();
}



BOOL CDlgMenuDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 이 함수 호출해서 등록한다.
	if (::TranslateAccelerator(m_hWnd, m_acc_key, pMsg)) {
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgMenuDlg::OnEditClearCmd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SetDlgItemText(IDC_STATE_EDIT, _T(""));
}
