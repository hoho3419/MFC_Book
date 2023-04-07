#pragma once

// MyServer 명령 대상
#include "MyUser.h"

class MyServer : public CSocket
{
private:
	MyUser m_user;

public:
	MyServer();
	virtual ~MyServer();
	virtual void OnAccept(int nErrorCode);
};


