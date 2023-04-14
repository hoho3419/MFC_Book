
// CalculatorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg 대화 상자



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, m_result(_T(""))
	, m_sample(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_cType = NOSTATE;
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_result);
	DDX_Text(pDX, IDC_EDIT2, m_sample);
	DDX_Control(pDX, IDC_RESULT_LIST, m_result_list);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_NUM0, IDC_DOT, &CCalculatorDlg::OnNumberBtnClick) // 0 ~ . 까지
	ON_CONTROL_RANGE(BN_CLICKED, IDC_PLUS, IDC_DIVISION, &CCalculatorDlg::OnOperBtnClick) // + ~ / 까지
	ON_BN_CLICKED(IDC_CALC, &CCalculatorDlg::OnBnClickedCalc)
	ON_BN_CLICKED(IDC_CLOSE, &CCalculatorDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_CLEAR, &CCalculatorDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_BACK, &CCalculatorDlg::OnBnClickedBack)
ON_WM_SIZING()
END_MESSAGE_MAP()


// CCalculatorDlg 메시지 처리기

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			/*
			HICON hIcon = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
			CStatic* pStatic = (CStatic*)GetDlgItem(IDD_ABOUTBOX);
			pStatic->SetIcon(hIcon);
			::DestroyIcon(hIcon);
			*/
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, TRUE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//m_num_bk_brush = ::CreateSolidBrush(RGB(255, 255, 255));

	CFont g_editFont;
	CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT1);

	g_editFont.CreatePointFont(200, TEXT("굴림"));
	pEdit1->SetFont(&g_editFont);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCalculatorDlg::OnPaint()
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
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalculatorDlg::OnNumberBtnClick(UINT ctlId)
{
	UpdateData(TRUE);

	switch (ctlId)
	{
	case IDC_NUM0:
		if (m_result.GetLength() == 1 && m_result[0] == '0') {
			return;
		}
		m_result += _T("0");
		break;
	case IDC_NUM1:
		m_result += _T("1");
		break;
	case IDC_NUM2:
		m_result += _T("2");
		break;
	case IDC_NUM3:
		m_result += _T("3");
		break;
	case IDC_NUM4:
		m_result += _T("4");
		break;
	case IDC_NUM5:
		m_result += _T("5");
		break;
	case IDC_NUM6:
		m_result += _T("6");
		break;
	case IDC_NUM7:
		m_result += _T("7");
		break;
	case IDC_NUM8:
		m_result += _T("8");
		break;
	case IDC_NUM9:
		m_result += _T("9");
		break;
	case IDC_DOT:
		if (m_result.GetLength() == 0 || m_result.Find('.') > 0 || m_result.GetAt(m_result.GetLength() - 1) == '.') {
			return;
		}
		m_result += _T(".");
		break;
	}
	UpdateData(FALSE);
}

void CCalculatorDlg::OperatorWay(Calculation ctlId, CString str)
{
	if (m_buf.IsEmpty() == 0 && m_result.IsEmpty() == 0) {
		OnBnClickedCalc();
		m_sample = m_buf + str;
	}
	else if (m_buf.IsEmpty() == 0 && m_result.IsEmpty() != 0) {
		m_sample = m_buf + str;
	}
	else if (m_cType == NOSTATE) {
		m_buf = m_result;
		m_sample = m_buf + str;
		m_result.Empty();
	}
	else if (m_cType != ctlId) {
		m_sample.Delete(m_sample.GetLength() - 3, 3);
		m_sample += str;
	}
	m_cType = ctlId;
}

void CCalculatorDlg::OnOperBtnClick(UINT ctlId)
{
	switch (ctlId)
	{
	case IDC_PLUS:
		OperatorWay(PLUS, _T(" + "));
		break;
	case IDC_MINUS:
		OperatorWay(MINUS, _T(" - "));
		break;
	case IDC_MULTI:
		OperatorWay(MULTI, _T(" * "));
		break;
	case IDC_DIVISION:
		OperatorWay(DIVISION, _T(" / "));
		break;
	}
	UpdateData(FALSE);
}

void CCalculatorDlg::OnBnClickedCalc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	double num1 = 0;
	double num2 = 0;
	double result = 0;

	num1 = _tstof(m_buf);
	num2 = _tstof(m_result);


	switch (m_cType)
	{
	case PLUS:
		result = num1 + num2;
		break;
	case MINUS:
		result = num1 - num2;
		break;
	case DIVISION:
		result = num1 / num2;
		break;
	case MULTI:
		result = num1 * num2;
		break;
	}
	if (floor(result) == result) {
		m_result.Format(_T("%d"), (int)result);
		m_sample.Format(_T("%d"), (int)result);
	}
	else {
		m_result.Format(_T("%g"), result);
		m_sample.Format(_T("%2f"), result);
	}
	m_buf = m_result;
	m_cType = NOSTATE;
	UpdateData(FALSE);
	m_result.Empty();
}


void CCalculatorDlg::OnBnClickedClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (MessageBox(_T("정말로 계산기를 닫으시겠습니까?"), _T("계산기"), MB_OKCANCEL) == IDOK) {
		::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
	}
}


void CCalculatorDlg::OnBnClickedClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_result.Empty();
	m_sample.Empty();
	m_buf.Empty();
	m_cType = NOSTATE;
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_result.Delete(m_result.GetLength() - 1, 1);
	UpdateData(FALSE);

	/*
	int temp = m_sample.GetLength();
	if (m_result.IsEmpty() == 0) {
		if (m_sample.GetAt(temp - 1) == ' ') {
			m_sample.Delete(m_sample.GetLength() - 3, 3);
		}
		else {
			m_sample.Delete(m_sample.GetLength() - 1, 1);
		}
		m_result.Delete(m_result.GetLength() - 1, 1);
		UpdateData(FALSE);
	}
	UpdateData(FALSE);

	*/
}


void CCalculatorDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);
	int width = pRect->right - pRect->left;
	CFont g_editFont;

	g_editFont.CreatePointFont(width - 650, TEXT("굴림"));
	for (int i = 0; i < 20; i++)
	{
		GetDlgItem(IDC_EDIT1 + i)->SetFont(&g_editFont);
	}
	g_editFont.DeleteObject();
}


//HBRUSH CCalculatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
//	int control_id = pWnd->GetDlgCtrlID();
//	if (control_id >= IDC_NUM0 && control_id <= IDC_DOT)
//	{
//		pDC->SetTextColor(RGB(0, 245, 0));
//		pDC->SetBkColor(RGB(255, 255, 255));
//		return m_num_bk_brush;
//	}
//
//
//	return hbr;
//}


//void CCalculatorDlg::OnDestroy()
//{
//	CDialogEx::OnDestroy();
//	DeleteObject(m_num_bk_brush);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//}


//void CCalculatorDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
//{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 색을 변경할 버튼(IDC_BUTTON1)을 그릴차례에 우리가 직접 색을 변경해줌
//	if (nIDCtl >= IDC_NUM0 && nIDCtl <= IDC_DOT)
//	{
//		CDC dc;
//		dc.Attach(lpDrawItemStruct->hDC);
//		{
//			RECT rtBtn = lpDrawItemStruct->rcItem;						// 버튼의 크기 가져옴
//			dc.Draw3dRect(&rtBtn, RGB(255, 255, 255), RGB(0, 0, 0));	// 버튼의 외곽선
//
//			dc.SetBkColor(RGB(255, 255, 255));		// 글자의 배경색상
//			dc.SetTextColor(RGB(0, 0, 0));			// 글자의 색상
//			CString str;
//			for (int i = 0; i < 11; i++)
//			{
//				str.Format(_T("%d"), i);
//				GetWindowText(str);
//				dc.DrawText(str, &rtBtn, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//				str.Empty();
//			}
//		}
//		dc.Detach();
//	}
//
//	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
//}
