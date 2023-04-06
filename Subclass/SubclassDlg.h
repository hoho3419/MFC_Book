
// SubclassDlg.h: 헤더 파일
//

#pragma once
#include "MyBtn.h"

// CSubclassDlg 대화 상자
class CSubclassDlg : public CDialogEx
{
private:
	MyBtn m_inc_btn, m_dec_btn;
// 생성입니다.
public:
	CSubclassDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUBCLASS_DIALOG };
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
	afx_msg void OnBnClickedIncBtn();
	afx_msg void OnBnClickedDecBtn();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
