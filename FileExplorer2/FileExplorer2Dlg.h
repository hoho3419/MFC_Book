
// FileExplorer2Dlg.h: 헤더 파일
//

#pragma once
#include "CFileFindEx.h"
#include "CListCtrlEx.h"


// CFileExplorer2Dlg 대화 상자
class CFileExplorer2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CFileExplorer2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEEXPLORER2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bSub;
	CButton m_stop_btn;
	CButton m_start_btn;
	CString m_FileLocation;
	CString m_FileName;
	CStatic m_status;
	BOOL m_bStop;
	CString m_token;
	CImageList m_img;
	CListCtrlEx m_list_result;
	//CListCtrl m_list_result;
	void SearFileNotSub();
	void SearFile(CString strStartFolder);
	afx_msg void OnBnClickedStartBtn();
	afx_msg void OnBnClickedStopBtn();
};
