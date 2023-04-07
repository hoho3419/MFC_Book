
// NodePadView.cpp: CNodePadView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "NodePad.h"
#endif

#include "NodePadDoc.h"
#include "NodePadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNodePadView

IMPLEMENT_DYNCREATE(CNodePadView, CEditView)

BEGIN_MESSAGE_MAP(CNodePadView, CEditView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CNodePadView 생성/소멸

CNodePadView::CNodePadView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CNodePadView::~CNodePadView()
{
}

BOOL CNodePadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 자동 래핑을 사용합니다.

	return bPreCreated;
}

void CNodePadView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CNodePadView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CNodePadView 진단

#ifdef _DEBUG
void CNodePadView::AssertValid() const
{
	CEditView::AssertValid();
}

void CNodePadView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CNodePadDoc* CNodePadView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNodePadDoc)));
	return (CNodePadDoc*)m_pDocument;
}
#endif //_DEBUG


// CNodePadView 메시지 처리기
