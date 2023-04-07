// MyClient.cpp: 구현 파일
//

#include "pch.h"
#include "ValueClient.h"
#include "MyClient.h"


// MyClient

MyClient::MyClient()
{
}

MyClient::~MyClient()
{
}


// MyClient 멤버 함수


void MyClient::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (nErrorCode != 0) {
		AfxMessageBox(_T("서버 응답에 실패 하였습니다."));
		return;
	}
	TRACE(_T("\n%d==================="), nErrorCode);

	int value;
	CString str = _T("성공");
	Receive(&value, sizeof(int));
	AfxGetMainWnd()->SetDlgItemInt(IDC_REC_EDIT,value);
	CListBox* m_rec_box = (CListBox*)AfxGetMainWnd()->GetDlgItem(IDC_REC_LIST);

	m_rec_box->InsertString(-1, str);

	CSocket::OnReceive(nErrorCode);
}
