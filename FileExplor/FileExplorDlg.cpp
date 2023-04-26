
// FileExplorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "FileExplor.h"
#include "FileExplorDlg.h"
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


// CFileExplorDlg 대화 상자



CFileExplorDlg::CFileExplorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILEEXPLOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileExplorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_Tree);
	DDX_Control(pDX, IDC_LIST, m_List);
}

BEGIN_MESSAGE_MAP(CFileExplorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, &CFileExplorDlg::OnTvnSelchangedTree)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CFileExplorDlg 메시지 처리기

BOOL CFileExplorDlg::OnInitDialog()
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
	InitTreeCtrl();


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFileExplorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileExplorDlg::OnPaint()
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
HCURSOR CFileExplorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileExplorDlg::InitTreeCtrl()
{
	// TODO: 여기에 구현 코드 추가.

	imageListNormal.Create(16, 16, ILC_COLOR32, 2, 2);
	imageListSelected.Create(16, 16, ILC_COLOR32, 2, 2);

	HICON hIconNormal = AfxGetApp()->LoadIcon(IDI_ICON1);  // 선택되지 않은 상태 아이콘 로드
	HICON hIconSelected = AfxGetApp()->LoadIcon(IDI_ICON2);

	// 처음 문자열을 삽입 후 삽입된 트리에 핸들을 반환 -> 삽입된 핸들과 삽입전 핸들값은 서로 다르다.
	HTREEITEM hItem = m_Tree.InsertItem(_T("C:"));
	// 현재 디렉토리를 찾을때 사용되는 클래스 생성
	CFileFind finder;
	// 파일을 찾고 찾았으면 TRUE를 반환
	BOOL bWorking = finder.FindFile(_T("C:\\*.*"));
	while (bWorking) {
		// 다음 파일을 찾고 결과를 리턴
		bWorking = finder.FindNextFile();
		// 폴더만 넣을 수 있게 조건문 생성
		if (finder.IsDirectory()) {
			// 폴더 이름을 삽입하고 C: 문자열이 삽입된 트리 컨트롤의 핸들값에 삽입한다.
			m_Tree.InsertItem(finder.GetFileName(), hItem);
		}
	}
	// 이 핸들값에 있는 정보들을 보여주는걸 보장하는 함수
	m_Tree.EnsureVisible(hItem);
}


void CFileExplorDlg::OnTvnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	CString pathSelected;
	HTREEITEM hSelected = pNMTreeView->itemNew.hItem;
	HTREEITEM hParentItem = hSelected;
	CFileFind finder;
	BOOL bWorking;
	/*
	TVINSERTSTRUCT  TI;
	TI.hParent = TVI_ROOT;      
	TI.hInsertAfter = TVI_LAST;  
	TI.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	TI.item.iImage = IDI_ICON1;                
	TI.item.iSelectedImage = IDI_ICON2;   

	HTREEITEM hTreeItem = m_Tree.InsertItem(&TI); 
	*/
	while (hParentItem != NULL)
	{
		pathSelected = _T("\\") + pathSelected;
		pathSelected = m_Tree.GetItemText(hParentItem) + pathSelected;
		hParentItem = m_Tree.GetParentItem(hParentItem);
	}

	pathSelected = pathSelected + _T("*.*");
	bWorking = finder.FindFile(pathSelected);

	if (m_Tree.GetItemData(hSelected) == 0){
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDots()) {
				continue;
			}
			if (finder.IsDirectory()) {
				m_Tree.InsertItem(finder.GetFileName(), hSelected);
			}
		}
		m_Tree.SetItemData(hSelected, 1);
		m_Tree.EnsureVisible(hSelected);
	}

	//  2.1 TreeView의 폴더를 마우스로 클릭하면, ListCtrl에 담겨있던 아이템을 비운다.
	if (pNMTreeView->itemNew.hItem != pNMTreeView->itemOld.hItem)
	{
		m_List.DeleteAllItems();
	}
	//  2.2 트리뷰에서 선택한 아이템의 하위폴더와 파일을 ListView에 보여준다.
	bWorking = finder.FindFile(pathSelected);
	while (bWorking) {
		bWorking = finder.FindNextFile();
		if (finder.IsDots()) continue;
		m_List.InsertItem(1, finder.GetFileName());
	}

	*pResult = 0;
}


void CFileExplorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CWnd* pTree = GetDlgItem(IDC_TREE);
	CWnd* pList = GetDlgItem(IDC_LIST);
	CWnd* pOk = GetDlgItem(IDOK);
	CWnd* pCancel = GetDlgItem(IDCANCEL);
	if (pTree == NULL) {return;}
	if (pList == NULL) {return;}
	if (pOk == NULL) {return;}
	if (pCancel == NULL) {return;}

	CRect rTree;
	CRect rList;
	CRect rOk;
	CRect rCancel;

	pTree->GetWindowRect(&rTree);
	pList->GetWindowRect(&rList);
    pOk->GetWindowRect(&rOk);
	pCancel->GetWindowRect(&rCancel);    

	ScreenToClient(&rTree);
	ScreenToClient(&rList);
    ScreenToClient(&rOk);
	ScreenToClient(&rCancel);

	pTree->SetWindowPos(NULL,
		rTree.left,
		rTree.top,
		cx / 2 - rTree.left,
		cy - rTree.top - 3 * rTree.top,
		SWP_NOZORDER);

	pList->SetWindowPos(NULL,
		rTree.left + rTree.Width(),
		rList.top,
		cx / 2 - rTree.left,
		cy - rTree.top - 3 * rTree.top,
		SWP_NOZORDER);

	pOk->SetWindowPos(NULL,
		rTree.left + rTree.Width() + rList.Width() - rCancel.Width() - rOk.Width() - 10,
		rList.top + rList.Height() + 3,
		rOk.Width(),
		rOk.Height(),
		SWP_NOZORDER);

	pCancel->SetWindowPos(NULL,
		rTree.left + rTree.Width() + rList.Width() - rCancel.Width(),
		rList.top + rList.Height() + 3,
		rCancel.Width(),
		rCancel.Height(),
		SWP_NOZORDER);
}


void CFileExplorDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lpMMI->ptMinTrackSize.x = 640;
	lpMMI->ptMinTrackSize.y = 480;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
