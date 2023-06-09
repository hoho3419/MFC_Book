﻿
// WebBrowerView.h: CWebBrowerView 클래스의 인터페이스
//

#pragma once


class CWebBrowerView : public CHtmlView
{
protected: // serialization에서만 만들어집니다.
	CWebBrowerView() noexcept;
	DECLARE_DYNCREATE(CWebBrowerView)

// 특성입니다.
public:
	CWebBrowerDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CWebBrowerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnWebsearchOpen();
	afx_msg void OnWebsearchForward();
	afx_msg void OnWebsearchBack();
};

#ifndef _DEBUG  // WebBrowerView.cpp의 디버그 버전
inline CWebBrowerDoc* CWebBrowerView::GetDocument() const
   { return reinterpret_cast<CWebBrowerDoc*>(m_pDocument); }
#endif

