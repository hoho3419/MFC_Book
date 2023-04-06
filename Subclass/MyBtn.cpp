// MyBtn.cpp: 구현 파일
//

#include "pch.h"
#include "Subclass.h"
#include "MyBtn.h"


// MyBtn

IMPLEMENT_DYNAMIC(MyBtn, CButton)

MyBtn::MyBtn()
{

}

MyBtn::~MyBtn()
{
}


BEGIN_MESSAGE_MAP(MyBtn, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// MyBtn 메시지 처리기




void MyBtn::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 0.5초 동안 눌렀는지 확인하는 타이머
	SetTimer(1, 500, NULL);


	CButton::OnLButtonDown(nFlags, point);
}


void MyBtn::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 클릭을 뗀다면 삭제한다.
	KillTimer(1);
	KillTimer(2);

	CButton::OnLButtonUp(nFlags, point);
}


void MyBtn::OnTimer(UINT_PTR nIDEvent)
{
	// 0.5초동안 눌렀다면 타이머가 시작되기 때문에 이 함수가 실행되고 
	if (nIDEvent == 1) {
		// nIDEvent 타이머 값이 1이라면 삭제하고 
		KillTimer(1);
		// 새로운 2타이머를 생성하기 때문에 
		SetTimer(2, 100, NULL);
	}
	else if (nIDEvent == 2) { // 이 else if  == 2로 들어온다.
		// GetDlgCtrlID를 통해서 모든 버튼 에디트에 적용되게 한다. 정해진 ID를 쓰게 되면 그 ID만 이 효과가 적용된다.
		GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), 20000), (LPARAM)m_hWnd);
	}
	CButton::OnTimer(nIDEvent);
}
