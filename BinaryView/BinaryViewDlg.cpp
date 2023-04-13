
// BinaryViewDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "BinaryView.h"
#include "BinaryViewDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBinaryViewDlg 대화 상자



CBinaryViewDlg::CBinaryViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BINARYVIEW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBinaryViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BIN_DATA_LIST, m_bin_data_list);
}

BEGIN_MESSAGE_MAP(CBinaryViewDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SELECT_BTN, &CBinaryViewDlg::OnBnClickedSelectBtn)
END_MESSAGE_MAP()


// CBinaryViewDlg 메시지 처리기

BOOL CBinaryViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_font.CreatePointFont(128, _T("굴림체"));
	m_bin_data_list.SetFont(&m_font);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CBinaryViewDlg::OnPaint()
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
HCURSOR CBinaryViewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBinaryViewDlg::OnBnClickedSelectBtn()
{
	CFileDialog ins_dlg(TRUE);// TRUE면 파일열기, FALSE면 다른 이름으로 저장
	if (IDOK == ins_dlg.DoModal()) {
		m_bin_data_list.ResetContent();
		SetDlgItemText(IDC_PATH_STATIC, ins_dlg.GetPathName());

		FILE* p_file = NULL;
		// 유니코드이기 때문에 _wfopen_s로 열고 바이너리 형식으로 rb한다.
		if (0 == _wfopen_s(&p_file, ins_dlg.GetPathName(), _T("rb"))) {
			CString total_str, str;
			if (p_file == NULL) {
				return;
			}
			UINT temp[24];
			int leng = 24, line = 1;
			while (leng == 24)
			{
				leng = fread(temp, 1, 24, p_file);
				if (leng > 0) {
					total_str.Format(_T("%06d :  "), line++);
					for (int i = 0; i < 24; i++)
					{
						str.Format(_T(" %02X "), temp[i]);
						total_str += str;
					}
					m_bin_data_list.InsertString(-1, total_str);
				}
			}
			if (fclose(p_file) == 0) {
			}
			/*
			if (p_file == NULL) {
				return;
			}
			wchar_t str[128];
			UINT temp[24];
			int leng = 24, line = 1, str_len;
			while (leng == 24)
			{
				leng = fread(temp, 1, 24, p_file);
				if (leng > 0) {
					str_len =  swprintf_s(str,128,_T("%06d :  "), line++);
					for (int i = 0; i < 24; i++)
					{
						str_len += swprintf_s(str + str_len, 128 - str_len ,_T(" %02X "), temp[i]);
					}
					m_bin_data_list.InsertString(-1, str);
				}
			}
			if (fclose(p_file) == 0) {
			}
			*/
		}

	}
}
