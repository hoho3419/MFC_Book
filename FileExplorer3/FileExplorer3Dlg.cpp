
// FileExplorer3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "FileExplorer3.h"
#include "FileExplorer3Dlg.h"
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


// CFileExplorer3Dlg 대화 상자



CFileExplorer3Dlg::CFileExplorer3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILEEXPLORER3_DIALOG, pParent)
{
	nIndexNormal = 0;
	nIndexSelected = 0;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CFileExplorer3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DIR_TREE1, m_Tree);
}

BEGIN_MESSAGE_MAP(CFileExplorer3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_DIR_TREE1, &CFileExplorer3Dlg::OnTvnSelchangedDirTree1)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_DIR_TREE1, &CFileExplorer3Dlg::OnTvnItemexpandedDirTree1)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_DIR_TREE1, &CFileExplorer3Dlg::OnTvnItemexpandingDirTree1)
END_MESSAGE_MAP()


// CFileExplorer3Dlg 메시지 처리기

BOOL CFileExplorer3Dlg::OnInitDialog()
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
	hIconNormal = AfxGetApp()->LoadIcon(IDI_OPEN_ICON);
	hIconSelected = AfxGetApp()->LoadIcon(IDI_CLOSE_ICON);

	imageListNormal.Create(16, 16, ILC_COLOR32, 2, 2);
	nIndexSelected = imageListNormal.Add(hIconSelected);
	nIndexNormal = imageListNormal.Add(hIconNormal); 

	m_Tree.SetImageList(&imageListNormal, TVSIL_NORMAL);  // 선택되지 않은 상태 이미지 리스트를 트리 컨트롤에 설정
	// m_Tree.SetImageList(&imageListNormal, TVSIL_STATE);

	HTREEITEM hItem = m_Tree.InsertItem(_T("CCCC"), nIndexNormal, nIndexNormal);

	CFileFind finder;
	BOOL bWorking = finder.FindFile(_T("C:\\*.*"));
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory()) {
			m_Tree.InsertItem(finder.GetFileName(), nIndexNormal, nIndexNormal, hItem);
		}
	}
	m_Tree.EnsureVisible(hItem);
	

	/*
	 - 처음부터 선택된 상태로 만들기 
	m_Tree.SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);  // 항목을 선택된 상태로 설정
	m_Tree.SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED | TVIS_STATEIMAGEMASK);  // 선택된 상태 아이콘으로 변경
	m_Tree.SetItemState(hItem, 0, TVIS_SELECTED | TVIS_STATEIMAGEMASK);

	 - 컨트롤에 변수를 추가하지 않고 사용하는 법
	CWnd* pCtrl = GetDlgItem(IDC_DIR_TREE);
	if (pCtrl != NULL && pCtrl->GetSafeHwnd() != NULL)
	{
		CTreeCtrl* pTreeCtrl = (CTreeCtrl*)pCtrl;
		HTREEITEM hParent = pTreeCtrl->GetRootItem();
		HTREEITEM hNew = pTreeCtrl->InsertItem(_T("새 항목"), hParent);
	}
	*/

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFileExplorer3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileExplorer3Dlg::OnPaint()
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
HCURSOR CFileExplorer3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileExplorer3Dlg::OnTvnSelchangedDirTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);


	*pResult = 0;
}


void CFileExplorer3Dlg::OnTvnItemexpandedDirTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	OutputDebugString(_T("22222222222222222222"));
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// 트리 컨트롤 항목이 확장되었을 때만 실행
	if ((pNMTreeView->action & TVE_EXPAND) && (pNMTreeView->itemNew.hItem != NULL))
	{
		HTREEITEM hItem = pNMTreeView->itemNew.hItem;
		m_Tree.SetItemImage(hItem, nIndexSelected, nIndexSelected);
		/*
		HTREEITEM hParentItem = pNMTreeView->itemNew.hItem;
		HTREEITEM hChildItem = m_Tree.GetChildItem(hParentItem);

		while (hChildItem != NULL)
		{
			int nState = m_Tree.GetItemState(hChildItem, TVIS_SELECTED | TVIS_STATEIMAGEMASK);
			if (nState == INDEXTOSTATEIMAGEMASK(1)) // 선택되어 있는 경우
			{
				int nImage = m_Tree.GetItemImage(hChildItem, nIndexNormal, nIndexSelected);
				if (nImage != nIndexSelected) // 선택된 상태 아이콘이 아닌 경우에만 변경
				{
					m_Tree.SetItemImage(hChildItem, nIndexSelected, nIndexSelected);
				}
			}
			else // 선택되어 있지 않은 경우
			{
				int nImage = m_Tree.GetItemImage(hChildItem, nIndexNormal, nIndexSelected);
				if (nImage != nIndexNormal) // 선택되지 않은 상태 아이콘이 아닌 경우에만 변경
				{
					m_Tree.SetItemImage(hChildItem, nIndexNormal, nIndexNormal);
				}
			}
			hChildItem = m_Tree.GetNextSiblingItem(hChildItem);
		}
		*/
	}
	*pResult = 0;
}


void CFileExplorer3Dlg::OnTvnItemexpandingDirTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 트리 컨트롤 항목이 확장되었을 때만 실행
	OutputDebugString(_T("Asdsakjfkjsdbgkjsbdk"));
	/*
	if ((pNMTreeView->action & TVE_EXPAND) && (pNMTreeView->itemNew.hItem != NULL))
	{
		HTREEITEM hParentItem = pNMTreeView->itemNew.hItem;
		HTREEITEM hChildItem = m_Tree.GetChildItem(hParentItem);

		while (hChildItem != NULL)
		{
			int nState = m_Tree.GetItemState(hChildItem, TVIS_SELECTED | TVIS_STATEIMAGEMASK);
			if (nState == INDEXTOSTATEIMAGEMASK(1)) // 선택되어 있는 경우
			{
				int nImage = m_Tree.GetItemImage(hChildItem, nIndexNormal, nIndexSelected);
				if (nImage != nIndexSelected) // 선택된 상태 아이콘이 아닌 경우에만 변경
				{
					m_Tree.SetItemImage(hChildItem, nIndexSelected, nIndexSelected);
				}
			}
			else // 선택되어 있지 않은 경우
			{
				int nImage = m_Tree.GetItemImage(hChildItem, nIndexNormal, nIndexSelected);
				if (nImage != nIndexNormal) // 선택되지 않은 상태 아이콘이 아닌 경우에만 변경
				{
					m_Tree.SetItemImage(hChildItem, nIndexNormal, nIndexNormal);

				}
			}
			hChildItem = m_Tree.GetNextSiblingItem(hChildItem);
		}
	}
	*/
	*pResult = 0;
}
