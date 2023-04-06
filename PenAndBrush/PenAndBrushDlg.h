
// PenAndBrushDlg.h: 헤더 파일
//

#pragma once
#include "TW_ListBox.h"

#ifdef _DEBUG 
	#pragma comment(lib, "DSH_TW_ListBox.lib") 
#else
	#pragma comment(lib, "RST_TW_ListBox.lib") 
#endif 

class MyColorListBox : public TW_ListBox
{
public :
	void DrawUserItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag)
	{
		COLORREF color = GetItemData(a_index);
		CRect r(ap_rect->left + 2, ap_rect->top + 2, ap_rect->right - 2, ap_rect->bottom - 2);
		ap_dc->FillSolidRect(r, color);
	}
};
// CPenAndBrushDlg 대화 상자
class CPenAndBrushDlg : public CDialogEx
{
private:
	MyColorListBox m_color_list;
	COLORREF m_pen_color = RGB(0,0,0), m_brush_color = RGB(255, 255, 255);
// 생성입니다.
public:
	CPenAndBrushDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PENANDBRUSH_DIALOG };
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
	afx_msg void OnLbnSelchangeColorList();
};
