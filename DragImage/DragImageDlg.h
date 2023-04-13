
// DragImageDlg.h: 헤더 파일
//

#pragma once


// CDragImageDlg 대화 상자
class CDragImageDlg : public CDialogEx
{
private: 
	CImage m_image;
	CPoint m_image_pos;
	CPoint m_prev_pos;
	char m_image_flag = 0;
// 생성입니다.
public:
	CDragImageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAGIMAGE_DIALOG };
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOk();
	afx_msg void OnDestroy();
};
