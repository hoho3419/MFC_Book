
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
ON_COMMAND(ID_DESTROY_BTN, &CCalculatorDlg::OnDestroyBtn)
ON_NOTIFY(NM_RCLICK, IDC_RESULT_LIST, &CCalculatorDlg::OnNMRClickResultList)
ON_STN_CLICKED(IDC_DES_PICTURE, &CCalculatorDlg::OnStnClickedDesPicture)
ON_NOTIFY(NM_DBLCLK, IDC_RESULT_LIST, &CCalculatorDlg::OnNMDblclkResultList)
//ON_WM_KEYDOWN()
ON_WM_CTLCOLOR()
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
	m_result_list.InsertColumn(1, _T("결과값"), LVCFMT_CENTER, 160, 1);
	m_result_list.InsertColumn(2, _T("날짜"), LVCFMT_CENTER, 173, 2);
	m_result_list.InsertColumn(3, _T("시간"), LVCFMT_CENTER, 150, 3);
	m_result_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


	// EDIT1 폰트 작업 크기 초기화
	CFont g_editFont;
	CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit1->EnableWindow(FALSE);
	g_editFont.CreatePointFont(350, TEXT("굴림"));
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
	if (m_cType == RESTATE) {
		m_result.Empty();
		m_sample.Empty();
		m_buf.Empty();
		m_cType = NOSTATE;
	}
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
	UpdateData(FALSE);
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
}

void CCalculatorDlg::OnBnClickedCalc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	double num1 = 0;
	double num2 = 0;
	double result = 0;
	CString y_day;
	CString t_sec;
	CTime c_tm = CTime::GetCurrentTime();
	y_day = c_tm.Format("%y-%m-%d");
	t_sec = c_tm.Format("%H:%M:%S");

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
		m_sample.Format(_T("%g"), result);
	}
	m_buf = m_result;
	m_cType = RESTATE;
	UpdateData(FALSE);
	ResultAdd(m_result, y_day, t_sec);
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
	GetDlgItem(IDC_EDIT1)->SetFocus();
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

	/*
	CFont   font;
	LOGFONT        LogFont;
	// Edit 컨트롤의 Font 정보를 LogFont에 가져옵니다.
	// GetDlgItem(IDC_EDIT1)->GetFont()->GetLogFont(&LogFont);
	// Font 글자 설정
	LogFont.lfWeight = 800;      // 굵기설정( MAX : 1000 )
	LogFont.lfHeight = 14;
	// LogFont의정보로설정
	font.CreateFontIndirect(&LogFont);
	// EDit 박스의 폰트를 설정합니다. 
	GetDlgItem(IDC_NUM0)->SetFont(&font);

	* 화면 가로 크기 값 구해서 폰트 크기 계속 바꿔주기
	int width = pRect->right - pRect->left;
	CFont g_editFont;

	//g_editFont.CreatePointFont(width - 750, TEXT("굴림"));/
	for (int i = 0; i < 20; i++)
	{
		GetDlgItem(IDC_EDIT1 + i)->SetFont(&g_editFont);
	}
	g_editFont.DeleteObject();
	*/
}


void CCalculatorDlg::ResultAdd(CString result, CString day, CString time)
{
	int count = 0;
	LVITEM lvitem;
	count = m_result_list.GetItemCount();

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = count;
	lvitem.iSubItem = 0;
	lvitem.pszText = result.GetBuffer(0);
	m_result_list.InsertItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = count; 
	lvitem.iSubItem = 1;
	lvitem.pszText = day.GetBuffer(0);
	m_result_list.SetItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = count;
	lvitem.iSubItem = 2;
	lvitem.pszText = time.GetBuffer(0);
	m_result_list.SetItem(&lvitem);

	/*
	m_result_list.InsertItem(1, _T("3131"), 0);
	m_result_list.SetItemText(0, 1, _T("안녕"));
	m_result_list.SetItemText(0, 2, _T("Hi"));
	*/

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


void CCalculatorDlg::OnDestroyBtn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int sel = m_result_list.GetSelectionMark();
	if (sel != -1) {
		m_result_list.DeleteItem(sel);
	}
	else {
		AfxMessageBox(_T("컬럼을 선택하세요"));
	}
}


void CCalculatorDlg::OnNMRClickResultList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMenu menu;
	menu.LoadMenu(IDR_DES_MENU);
	CMenu* p_sub_menu = menu.GetSubMenu(0);

	CPoint pos;
	GetCursorPos(&pos);
	
	p_sub_menu->TrackPopupMenu(TPM_LEFTALIGN, pos.x, pos.y, this);
	menu.DestroyMenu();
	*pResult = 0;
}



void CCalculatorDlg::OnStnClickedDesPicture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (MessageBox(_T("기록을 전부 삭제하시겠습니까?"), _T("경고"), MB_OKCANCEL) == IDOK) {
		m_result_list.DeleteAllItems();
	}
}


void CCalculatorDlg::OnNMDblclkResultList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = m_result_list.GetSelectionMark();
	CString str = m_result_list.GetItemText(sel, 0);
	m_result = str;
	m_sample = str;
	*pResult = 0;
	UpdateData(FALSE);
}



BOOL CCalculatorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN){
		switch (pMsg->wParam)
		{
		case VK_NUMPAD0:
			OnNumberBtnClick(IDC_NUM0);
			break;
		case VK_NUMPAD1:
			OnNumberBtnClick(IDC_NUM1);
			break;
		case VK_NUMPAD2:
			OnNumberBtnClick(IDC_NUM2);
			break;
		case VK_NUMPAD3:
			OnNumberBtnClick(IDC_NUM3);
			break;
		case VK_NUMPAD4:
			OnNumberBtnClick(IDC_NUM4);
			break;
		case VK_NUMPAD5:
			OnNumberBtnClick(IDC_NUM5);
			break;
		case VK_NUMPAD6:
			OnNumberBtnClick(IDC_NUM6);
			break;
		case VK_NUMPAD7:
			OnNumberBtnClick(IDC_NUM7);
			break;
		case VK_NUMPAD8:
			OnNumberBtnClick(IDC_NUM8);
			break;
		case VK_NUMPAD9:
			OnNumberBtnClick(IDC_NUM9);
			break;
		case VK_OEM_PERIOD:
			OnNumberBtnClick(IDC_DOT);
			break;
		case VK_ADD:
			OperatorWay(PLUS, _T(" + "));
			break;
		case VK_SUBTRACT:
			OperatorWay(MINUS, _T(" - "));
			break;
		case VK_MULTIPLY:
			OperatorWay(MULTI, _T(" * "));
			break;
		case VK_DIVIDE:
			OperatorWay(DIVISION, _T(" / "));
			break;
		case VK_OEM_PLUS:
			OnBnClickedCalc();
			break;
		case VK_DELETE:
			OnBnClickedClear();
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CCalculatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
	{
		CBrush brush(RGB(255, 255, 255));

		pDC->SetBkColor((COLORREF)brush.GetSafeHandle());

		hbr = brush;
	}

	return hbr;
}
