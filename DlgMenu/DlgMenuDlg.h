
// DlgMenuDlg.h: 헤더 파일
//

#pragma once


// CDlgMenuDlg 대화 상자
class CDlgMenuDlg : public CDialogEx
{
private:
	int m_start_flag = 0;
	HACCEL m_acc_key;
// 생성입니다.
public:
	CDlgMenuDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGMENU_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void UpdateMenu();
	afx_msg void OnBnClickedStartBtn();
	afx_msg void OnBnClickedStopBtn();
	afx_msg void OnStartCmd();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEditClearCmd();
};
