
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bEqualClk = FALSE;
	m_cType = 0;
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_result);
	DDX_Text(pDX, IDC_EDIT1, m_result);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_NUM0, &CCalculatorDlg::OnBnClickedNum0)
	ON_BN_CLICKED(IDC_NUM1, &CCalculatorDlg::OnBnClickedNum1)
	ON_BN_CLICKED(IDC_NUM2, &CCalculatorDlg::OnBnClickedNum2)
	ON_BN_CLICKED(IDC_NUM3, &CCalculatorDlg::OnBnClickedNum3)
	ON_BN_CLICKED(IDC_NUM4, &CCalculatorDlg::OnBnClickedNum4)
	ON_BN_CLICKED(IDC_NUM5, &CCalculatorDlg::OnBnClickedNum5)
	ON_BN_CLICKED(IDC_NUM6, &CCalculatorDlg::OnBnClickedNum6)
	ON_BN_CLICKED(IDC_NUM7, &CCalculatorDlg::OnBnClickedNum7)
	ON_BN_CLICKED(IDC_NUM8, &CCalculatorDlg::OnBnClickedNum8)
	ON_BN_CLICKED(IDC_NUM9, &CCalculatorDlg::OnBnClickedNum9)
	ON_BN_CLICKED(IDC_DOT, &CCalculatorDlg::OnBnClickedDot)
	ON_BN_CLICKED(IDC_CALC, &CCalculatorDlg::OnBnClickedCalc)
	ON_BN_CLICKED(IDC_PLUS, &CCalculatorDlg::OnBnClickedPlus)
	ON_BN_CLICKED(IDC_MINUS, &CCalculatorDlg::OnBnClickedMinus)
	ON_BN_CLICKED(IDC_DIVISION, &CCalculatorDlg::OnBnClickedDivision)
	ON_BN_CLICKED(IDC_MULTI, &CCalculatorDlg::OnBnClickedMulti)
	ON_BN_CLICKED(IDC_CLOSE, &CCalculatorDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_CLEAR, &CCalculatorDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_BACK, &CCalculatorDlg::OnBnClickedBack)
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
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CFont g_editFont;
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);

	g_editFont.CreatePointFont(200, TEXT("굴림"));
	pEdit->SetFont(&g_editFont);

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


enum Calculation
{
	PLUS, MINUS, DIVISION, MULTI
};


void CCalculatorDlg::OnBnClickedNum0()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bEqualClk) {
		m_result.Empty();
		m_bEqualClk = FALSE;
	}
	m_result += _T("0");
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNum1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bEqualClk) {
		m_result.Empty();
		m_bEqualClk = FALSE;
	}
	m_result += _T("1");
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNum2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bEqualClk) {
		m_result.Empty();
		m_bEqualClk = FALSE;
	}
	m_result += _T("2");
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNum3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bEqualClk) {
		m_result.Empty();
		m_bEqualClk = FALSE;
	}
	m_result += _T("3");
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNum4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bEqualClk) {
		m_result.Empty();
		m_bEqualClk = FALSE;
	}
	m_result += _T("4");
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNum5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bEqualClk) {
		m_result.Empty();
		m_bEqualClk = FALSE;
	}
	m_result += _T("5");
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNum6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bEqualClk) {
		m_result.Empty();
		m_bEqualClk = FALSE;
	}
	m_result += _T("6");
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNum7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bEqualClk) {
		m_result.Empty();
		m_bEqualClk = FALSE;
	}
	m_result += _T("7");
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNum8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bEqualClk) {
		m_result.Empty();
		m_bEqualClk = FALSE;
	}
	m_result += _T("8");
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNum9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bEqualClk) {
		m_result.Empty();
		m_bEqualClk = FALSE;
	}
	m_result += _T("9");
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedDot()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bEqualClk) {
		m_result.Empty();
		m_bEqualClk = FALSE;
	}
	m_result += _T(".");
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
	}
	else {
		m_result.Format(_T("%.2f"), result);
	}
	UpdateData(FALSE);
	m_bEqualClk = TRUE;
}


void CCalculatorDlg::OnBnClickedPlus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cType = PLUS;
	m_buf = m_result;
	m_result.Empty();
}


void CCalculatorDlg::OnBnClickedMinus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cType = MINUS;
	m_buf = m_result;
	m_result.Empty();
}


void CCalculatorDlg::OnBnClickedDivision()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cType = DIVISION;
	m_buf = m_result;
	m_result.Empty();
}


void CCalculatorDlg::OnBnClickedMulti()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cType = MULTI;
	m_buf = m_result;
	m_result.Empty();
}


void CCalculatorDlg::OnBnClickedClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
}


void CCalculatorDlg::OnBnClickedClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_result.Empty();
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_result.Delete(m_result.GetLength() - 1, 1);
	UpdateData(FALSE);
}
