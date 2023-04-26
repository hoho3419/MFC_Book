
// Calculator2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Calculator2.h"
#include "Calculator2Dlg.h"
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


// CCalculator2Dlg 대화 상자



CCalculator2Dlg::CCalculator2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculator2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalculator2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_NUM0, IDC_DES_PICTURE, OnControlClick)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCalculator2Dlg 메시지 처리기

BOOL CCalculator2Dlg::OnInitDialog()
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
	mh_edit_bk = ::CreateSolidBrush(RGB(255, 255, 255));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCalculator2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalculator2Dlg::OnPaint()
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

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCalculator2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CCalculator2Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	int control_id = pWnd->GetDlgCtrlID();

	if ((control_id >= IDC_EDIT1) && (control_id <= IDC_EDIT2)) {
		return 	mh_edit_bk;
	}
	
	return hbr;
}

void CCalculator2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	DeleteObject(mh_edit_bk);
}

void CCalculator2Dlg::OnControlClick(UINT ctrlID)
{
	CString str;
	CString p_str;
	CString buf;
	//OutputDebugString(_T("aaaaaaaaa"));
	switch (ctrlID)
	{
	case IDC_NUM0:
		GetDlgItemText(IDC_NUM0, str);
		GetDlgItemText(IDC_EDIT1,p_str);
		p_str += str;
		SetDlgItemText(IDC_EDIT1, p_str);
		break;
	case IDC_NUM1:
		GetDlgItemText(IDC_NUM1, str);
		GetDlgItemText(IDC_EDIT1, p_str);
		p_str += str;
		SetDlgItemText(IDC_EDIT1, p_str);
		break;
	case IDC_NUM2:
		GetDlgItemText(IDC_NUM2, str);
		GetDlgItemText(IDC_EDIT1, p_str);
		p_str += str;
		SetDlgItemText(IDC_EDIT1, p_str);
		break;
	case IDC_NUM3:
		GetDlgItemText(IDC_NUM3, str);
		GetDlgItemText(IDC_EDIT1, p_str);
		p_str += str;
		SetDlgItemText(IDC_EDIT1, p_str);
		break;
	case IDC_NUM4:
		GetDlgItemText(IDC_NUM4, str);
		GetDlgItemText(IDC_EDIT1, p_str);
		p_str += str;
		SetDlgItemText(IDC_EDIT1, p_str);
		break;
	case IDC_NUM5:
		GetDlgItemText(IDC_NUM5, str);
		GetDlgItemText(IDC_EDIT1, p_str);
		p_str += str;
		SetDlgItemText(IDC_EDIT1, p_str);
		break;
	case IDC_NUM6:
		GetDlgItemText(IDC_NUM6, str);
		GetDlgItemText(IDC_EDIT1, p_str);
		p_str += str;
		SetDlgItemText(IDC_EDIT1, p_str);
		break;
	case IDC_NUM7:
		GetDlgItemText(IDC_NUM7, str);
		GetDlgItemText(IDC_EDIT1, p_str);
		p_str += str;
		SetDlgItemText(IDC_EDIT1, p_str);
		break;
	case IDC_NUM8:
		GetDlgItemText(IDC_NUM8, str);
		GetDlgItemText(IDC_EDIT1, p_str);
		p_str += str;
		SetDlgItemText(IDC_EDIT1, p_str);
		break;
	case IDC_NUM9:
		GetDlgItemText(IDC_NUM9, str);
		GetDlgItemText(IDC_EDIT1, p_str);
		p_str += str;
		SetDlgItemText(IDC_EDIT1, p_str);
		break;
	case IDC_DOT:
		GetDlgItemText(IDC_DOT, str);
		GetDlgItemText(IDC_EDIT1, p_str);
		p_str += str;
		SetDlgItemText(IDC_EDIT1, p_str);
		break;
	case IDC_PLUS:
		GetDlgItemText(IDC_EDIT2, str);
		if (str.IsEmpty() == FALSE){
			AfxExtractSubString(str, buf, 0, ' ');
			TRACE(_T("aaaaaaaaaaaaaaa  %s   aaaaaaaaaaaa"), str);
		}
		GetDlgItemText(IDC_EDIT1, str);
		SetDlgItemText(IDC_EDIT1, _T(""));
		SetDlgItemText(IDC_EDIT2, str + _T(" + "));
		break;
	case IDC_MINUS:
		break;
	case IDC_MULTI:
		break;
	case IDC_DIVISION:
		break;
	case IDC_CALC:
		break;
	case IDC_BACK:
		break;
	case IDC_CLEAR:
		break;
	case IDC_CLOSE:
		break;
	case IDC_DES_PICTURE:
		break;
	}
	UpdateData(FALSE);
}