// CListenSocket.cpp: 구현 파일
//

#include "pch.h"
#include "TCPServer2.h"
#include "CListenSocket.h"
#include "TCPServer2Doc.h"


// CListenSocket

CListenSocket::CListenSocket(CTCPServer2Doc* pDoc)
{
	m_pDoc = pDoc;
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 멤버 함수


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CSocket::OnAccept(nErrorCode);
	m_pDoc->ProcessAeccpt(nErrorCode);
}


//void CListenSocket::OnClose(int nErrorCode)
//{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

//	CSocket::OnClose(nErrorCode);
//}


//void CListenSocket::OnReceive(int nErrorCode)
//{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

//	CSocket::OnReceive(nErrorCode);
//}
