// MyUser.cpp: 구현 파일
//

#include "pch.h"
#include "ValueServer.h"
#include "MyUser.h"


// MyUser

MyUser::MyUser()
{
}

MyUser::~MyUser()
{
}


// MyUser 멤버 함수


void MyUser::OnReceive(int nErrorCode)
{

	/*
	int data;
	CString str;

	Receive(str, sizeof(CString) * 100);
	TRACE("%s", str);
	
	char buffer[1024];
	int bytesRead = Receive(buffer, 1024);
	CString str(buffer, bytesRead);

	AfxGetMainWnd()->SetDlgItemText(IDC_VALUE_EDIT, str);

	data = 1;
	Send(&data, sizeof(int));

	CSocket::OnReceive(nErrorCode);
	*/
}


void MyUser::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	Close();

	ShutDown(2);
	CSocket::OnClose(nErrorCode);
}
