
// CalculatorDlg.h: 헤더 파일
//

enum Calculation
{
	PLUS = 1, MINUS = 2, DIVISION = 3, MULTI = 4, NOSTATE = 5
};

#pragma once
// CCalculatorDlg 대화 상자
class CCalculatorDlg : public CDialogEx
{
private:
	//HBRUSH m_num_bk_brush;
// 생성입니다.
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
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
	CString m_result;
	CString m_sample;
	CString m_buf;
	Calculation m_cType;
	CListCtrl m_result_list;

	afx_msg void OnNumberBtnClick(UINT ctlId);
	afx_msg void OnOperBtnClick(UINT ctlId);
	afx_msg void OnBnClickedCalc();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedBack();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnDestroyBtn();
	afx_msg void OnNMRClickResultList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnClickedDesPicture();
	afx_msg void OnNMDblclkResultList(NMHDR* pNMHDR, LRESULT* pResult);
	void OperatorWay(Calculation ctlId, CString str);
	void CCalculatorDlg::ResultAdd();
};
