
// MoveRectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MoveRect.h"
#include "MoveRectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMoveRectDlg 대화 상자



CMoveRectDlg::CMoveRectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOVERECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMoveRectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMoveRectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMoveRectDlg 메시지 처리기

BOOL CMoveRectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_rect.SetRect(50, 50, 100, 100);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMoveRectDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{
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
		if (m_last_key_type) {
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(0, 200, 0));
			dc.SelectObject(GetFont());
			if (m_last_key_type == VK_LEFT) {
				dc.TextOut(m_rect.left - 20, m_rect.top + 15, _T("◀"));
			}else if (m_last_key_type == VK_RIGHT) {
				dc.TextOut(m_rect.left + 50, m_rect.top + 15, _T("▶"));
			}
			else if (m_last_key_type == VK_UP) {
				dc.TextOut(m_rect.left + 15, m_rect.top - 25, _T("▲"));
			}
			else if (m_last_key_type == VK_DOWN) {
				dc.TextOut(m_rect.left + 15, m_rect.top + 50, _T("▼"));
			}
		}

		dc.FillSolidRect(m_rect,RGB(0,200,0));
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMoveRectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMoveRectDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*
	switch (nChar)
	{
	case VK_LEFT:
		m_rect.left -= 20;
		m_rect.right -= 20;
			//50, 50, 100, 100
		break;
	}
	TRACE("000000000000000");
	*/
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

// 다이얼로그 포커스되기 전에 실행되서 처리 하기 때문에 만들어줘야함
BOOL CMoveRectDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			m_rect.left -= 20;
			m_rect.right -= 20;
			break;
		case VK_RIGHT:
			m_rect.left += 20;
			m_rect.right += 20;
			break;
		case VK_DOWN:
			m_rect.top += 20;
			m_rect.bottom += 20;
			break;
		case VK_UP:
			m_rect.top -= 20;
			m_rect.bottom -= 20;
			break;
		}
		m_last_key_type = pMsg->wParam;
		Invalidate();
		return 1;
	}
	else if (pMsg->message == WM_KEYUP) {
		if (pMsg->wParam >= VK_LEFT && pMsg->wParam <= VK_DOWN) {
			m_last_key_type = 0;
			Invalidate();
			return 1;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMoveRectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
