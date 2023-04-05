
// AddrArrayDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "AddrArray.h"
#include "AddrArrayDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAddrArrayDlg 대화 상자



CAddrArrayDlg::CAddrArrayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDRARRAY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAddrArrayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAddrArrayDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SHOW_BTN, &CAddrArrayDlg::OnBnClickedShowBtn)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAddrArrayDlg 메시지 처리기

BOOL CAddrArrayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 클래스에 브러쉬 멤버를 선언하고 OnInitDialog에서 에디트와 대화 상자가 다 만들어진 상태에서 브러시를 생성한다.
	m_bk_brush.CreateSolidBrush(RGB(0, 200, 255));


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAddrArrayDlg::OnPaint()
{
	if (IsIconic())
	{
		// 최소화 되었을때 모양이 변하는 구문이다.
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
		/*

		// 그릴수 있는 dc 객체를 선언
		CPaintDC dc(this);
		CRect r;
		// 현재 윈도우 객체 크기 가져오고
		GetClientRect(&r);
		// 만든 브러쉬로 테두리 없이 색을 채우기
		dc.FillRect(r, &m_bk_brush);

		// 만들어진 브러쉬를 선택하면 이전에 가지고 있던 브러쉬를 반환해주면
		CBrush * p_old_brush = dc.SelectObject(&m_bk_brush);
		// 현재 윈도우에 그린다.
		dc.Rectangle(r);
		// 이전 브러쉬를 받은걸 선택한 후에 
		dc.SelectObject(p_old_brush);
		// 도형을 그리면 이전에 등록되었던 브러시로 그려준다.
		dc.Rectangle(10,10,200,200);
		*/
		//dc.SelectObject(m_bk_brush);
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAddrArrayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAddrArrayDlg::OnBnClickedShowBtn()
{
	int num[16],i;
	
	for (i = 0; i < 11; i++)
	{
		num[i] = GetDlgItemInt(IDC_EDIT1 + i);
	}
	CString str, total_str;
	/*
	for (i = 0; i < 5; i++)
	{
		num[i] = GetDlgItemInt(1000 + i);
	}
	CComboBox* p_combo;
	CString str, total_str;
	int index;
	for (i = 0; i < 6; i++)
	{
		// 콤보 박스를 주소값을 받아와서 캐스팅하고
		p_combo = (CComboBox*)GetDlgItem(IDC_COMBO1 + i);
		// 뭘 선택했는지 확인한다.
		index = p_combo->GetCurSel();
		// 에러가 아니라면
		if (index != CB_ERR) {
			// 텍스트를 가져온다.
			p_combo->GetLBText(index, str);
			num[5 + i] = _tstof(str);
		}
		else {
			num[5 + i] = 0;
		}
	}
	*/
	for ( i = 0; i < 11; i++)
	{
		str.Format(_T("%d,"), num[i]);
		total_str = total_str + str;
	}

	SetDlgItemText(IDC_NUM_EDIT, total_str);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

/*
BOOL CAddrArrayDlg::OnEraseBkgnd(CDC* pDC)
{
	///BOOL flag = CDialogEx::OnEraseBkgnd(pDC); 전부 다 바꿔줄 게 아니라면 권장하는 작업이 아니다.
	// OnPaint 함수보다 먼저 실행되는 함수이기 때문에 윈도우 배경색을 바꾸는건 여기서 작업한다.
	CRect r;
	// 현재 윈도우 객체 크기 가져오고
	GetClientRect(&r);
	// 만든 브러쉬로 테두리 없이 색을 채우기
	pDC->FillRect(r, &m_bk_brush);
	
	// OnEraseBkgnd 함수 안에서 기본 배경색인 회색을 그리기 때문에 위에서 먼저 처리를 해주어야 한다.
	// return CDialogEx::OnEraseBkgnd(pDC);
	return TRUE;
}
*/

HBRUSH CAddrArrayDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// return (HBRUSH)::GetStockObject(NULL_BRUSH); 배경색 자체를 그리고 싶지 않을때 쓰는 구문
	
	if (nCtlColor == CTLCOLOR_DLG) {
		return m_bk_brush;
	}
	else if (nCtlColor == CTLCOLOR_EDIT) {
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(RGB(0,200,255));
		pDC->SetTextColor(RGB(255, 255, 255));
		return m_bk_brush;
	}
	else if (nCtlColor == CTLCOLOR_BTN) {
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		return m_bk_brush;
	}
	return hbr;
}
