#pragma once
#include "hsocket.h"

class CUDPDataHandle
{
public:
	virtual void HandleCallBack(sockaddr* from,
		char * pData,
		unsigned long DataLength) = 0;

};
class CUDPsocket :
	public CHsocket
{
public:
	CUDPsocket(void);
	~CUDPsocket(void);

	bool	Start(CUDPDataHandle	*pUDPDataHandle,int nPort = -1);
	void	Stop();

	int		SendData(const char* buf, int len, char *szAddress, int nPort);

	static DWORD	WINAPI	ThreadPtr(void *p);
	void   OnThreadPtr();
protected:
	CUDPDataHandle	*m_pUDPDataHandle;

	bool			 m_bContiune;
	HANDLE			 m_hThread;
};
