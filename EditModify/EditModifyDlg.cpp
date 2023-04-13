
// EditModifyDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "EditModify.h"
#include "EditModifyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEditModifyDlg 대화 상자



CEditModifyDlg::CEditModifyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDITMODIFY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEditModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEditModifyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CEditModifyDlg 메시지 처리기

BOOL CEditModifyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	for (int i = 0; i < 6; i++)
	{
		SetDlgItemText(IDC_EDIT1 + i, _T("안녕하세요"));
	}
	mh_edit_bk_brush = ::CreateSolidBrush(RGB(0, 255, 0));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CEditModifyDlg::OnPaint()
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
HCURSOR CEditModifyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CEditModifyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	int control_id = pWnd->GetDlgCtrlID();
	if (control_id >= IDC_EDIT1 && control_id <= IDC_EDIT6) {
		// 현재 윈도우 핸들 값 가져오는 구문
		HWND cur_foucus = ::GetFocus();
		// 현재 포커스 된 컨트롤만 색깔 바꾸기
		if (cur_foucus == pWnd->m_hWnd) {
			pDC->SetTextColor(RGB(255, 255, 255));
		}
		else {
			pDC->SetTextColor(RGB(0, 168, 168));
		}
		pDC->SetBkColor(RGB(0, 255, 0));
		return mh_edit_bk_brush;
	}

	return hbr;
}


void CEditModifyDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// onit에서 한번만 생성하고 지워줘야 한다.
	DeleteObject(mh_edit_bk_brush);
}
