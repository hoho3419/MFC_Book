
// FileExplorer3Dlg.h: 헤더 파일
//

#pragma once


// CFileExplorer3Dlg 대화 상자
class CFileExplorer3Dlg : public CDialogEx
{
private:
	CImageList imageListNormal;
	int nIndexNormal = 0;
	int nIndexSelected = 0;
// 생성입니다.
public:
	CFileExplorer3Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEEXPLORER3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	HICON hIconNormal;
	HICON hIconSelected;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_Tree;
	afx_msg void OnTvnSelchangedDirTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTvnItemexpandedDirTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTvnItemexpandingDirTree1(NMHDR* pNMHDR, LRESULT* pResult);
};
