
// RegistHotKeyDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "RegistHotKey.h"
#include "RegistHotKeyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRegistHotKeyDlg 대화 상자



CRegistHotKeyDlg::CRegistHotKeyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTHOTKEY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRegistHotKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRegistHotKeyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CRegistHotKeyDlg 메시지 처리기

BOOL CRegistHotKeyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	 
	// RegisterHotKey 함수로 m_hWnd 현재 윈도우 등록 후 26000 로 ID를 정하고 조합키를 안할거면 0 할거면 MOD_SHIFT를 하고
	// 누르면 반응할 VK_HOME 를 정한 다음 이벤트 메세지 함수를 등록해서 

	RegisterHotKey(m_hWnd, 26000, 0, VK_HOME); // MOD_SHIFT

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRegistHotKeyDlg::OnPaint()
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
HCURSOR CRegistHotKeyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRegistHotKeyDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// id 를 식별한 다음 하고 싶은 작업을 수행한다.
	if (nHotKeyId == 26000) {
		if (m_show_flag == 1) {
			ShowWindow(SW_HIDE);
		}
		else {
			ShowWindow(SW_SHOW);
		}
		m_show_flag = !m_show_flag;
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}
