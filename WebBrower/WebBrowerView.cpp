
// WebBrowerView.cpp: CWebBrowerView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "WebBrower.h"
#endif

#include "WebBrowerDoc.h"
#include "WebBrowerView.h"
#include "CMyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWebBrowerView

IMPLEMENT_DYNCREATE(CWebBrowerView, CHtmlView)

BEGIN_MESSAGE_MAP(CWebBrowerView, CHtmlView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CHtmlView::OnFilePrint)
	ON_COMMAND(ID_WEBSEARCH_OPEN, &CWebBrowerView::OnWebsearchOpen)
	ON_COMMAND(ID_WEBSEARCH_FORWARD, &CWebBrowerView::OnWebsearchForward)
	ON_COMMAND(ID_WEBSEARCH_BACK, &CWebBrowerView::OnWebsearchBack)
END_MESSAGE_MAP()

// CWebBrowerView 생성/소멸

CWebBrowerView::CWebBrowerView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CWebBrowerView::~CWebBrowerView()
{
}

BOOL CWebBrowerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CHtmlView::PreCreateWindow(cs);
}

void CWebBrowerView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// Navigate(_T("https://www.naver.com"));
	m_pBrowserApp->put_Silent(VARIANT_TRUE); // 스크립트 오류 표시 끄기
	GoHome();
}


// CWebBrowerView 인쇄



// CWebBrowerView 진단

#ifdef _DEBUG
void CWebBrowerView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CWebBrowerView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CWebBrowerDoc* CWebBrowerView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWebBrowerDoc)));
	return (CWebBrowerDoc*)m_pDocument;
}
#endif //_DEBUG


// CWebBrowerView 메시지 처리기


void CWebBrowerView::OnWebsearchOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMyDialog dlg;
	if (dlg.DoModal() == IDOK) {
		Navigate(dlg.m_url);
	}
}


void CWebBrowerView::OnWebsearchForward()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	GoBack();
}


void CWebBrowerView::OnWebsearchBack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	GoForward();
}
