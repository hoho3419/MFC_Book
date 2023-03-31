// CDataSocket.cpp: 구현 파일
//

#include "pch.h"
#include "TCPServer2.h"
#include "CDataSocket.h"
#include "TCPServer2Doc.h"


// CDataSocket

CDataSocket::CDataSocket(CTCPServer2Doc* pDoc)
{
	m_pDoc = pDoc;
}

CDataSocket::~CDataSocket()
{
}


// CDataSocket 멤버 함수


void CDataSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CSocket::OnClose(nErrorCode);
	m_pDoc->ProcessReceive(this, nErrorCode);
}


void CDataSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CSocket::OnReceive(nErrorCode);
	m_pDoc->ProcessClose(this, nErrorCode);
}
