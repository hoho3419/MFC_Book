#pragma once


// MyBtn

class MyBtn : public CButton
{
	DECLARE_DYNAMIC(MyBtn)

public:
	MyBtn();
	virtual ~MyBtn();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


