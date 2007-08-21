#include "stdafx.h"
#include ".\udpsocket.h"

int GetFreeSocketPort_1(int nBasePort)
{
	struct sockaddr_in addr, addr1;
	memset(&addr,0,sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(0);

	memset(&addr1,0,sizeof(struct sockaddr_in));
	addr1.sin_family = AF_INET;
	addr1.sin_addr.s_addr = htonl(0);
	while(nBasePort < 30000)
	{
		int sock = socket(PF_INET,SOCK_DGRAM,0);
		int sock1 = socket(PF_INET,SOCK_DGRAM,0);
		addr.sin_port = htons(nBasePort);
		addr1.sin_port = htons(nBasePort + 1);
		if (bind(sock,(struct sockaddr *)&addr,sizeof(struct sockaddr_in)) == 0&&
			bind(sock1,(struct sockaddr *)&addr1,sizeof(struct sockaddr_in)) == 0)
		{
			closesocket(sock);
			closesocket(sock1);
			return nBasePort;
		}
		closesocket(sock1);
		closesocket(sock);
		nBasePort += 2;
	}
	return 0;
}

CUDPsocket::CUDPsocket(void):
m_pUDPDataHandle(NULL),
m_bContiune(false),
m_hThread(0)
{
}

CUDPsocket::~CUDPsocket(void)
{
}
bool	CUDPsocket::Start(CUDPDataHandle	*pUDPDataHandle,int nPort)
{
	do {
		if(nPort < 0)
			nPort = GetFreeSocketPort_1(11000);
		if(!hsocket(nPort, SOCK_DGRAM))
			break;
		m_pUDPDataHandle = pUDPDataHandle;

		m_bContiune		 = true;
		m_hThread		 = CreateThread(NULL, 0, ThreadPtr, this, 0, NULL);
		return true;
	} while(false);

	Stop();
	return false;

}
void	CUDPsocket::Stop()
{
	m_bContiune = false;
	hclosesocket();
	if(m_hThread)
		WaitForSingleObject(m_hThread, INFINITE);
	m_hThread	= 0;
}
DWORD	CUDPsocket::ThreadPtr(void *p)
{
	reinterpret_cast<CUDPsocket*>(p)->OnThreadPtr();
	return 0;
}
void   CUDPsocket::OnThreadPtr()
{
	char buf[1024];
	int  len;
	int  recv_len;
	sockaddr from;
	while(m_bContiune)
	{
		len = 1024;
		memset(&from, 0, sizeof(from));
		recv_len = hrecvfrom(buf, len, &from);
		if(recv_len > 0 && m_pUDPDataHandle)
		{
			m_pUDPDataHandle->HandleCallBack(&from, buf, recv_len);
		}
	}
}
int		CUDPsocket::SendData(const char* buf, int len, char *szAddress, int nPort)
{
	sockaddr_in in;
	memset(&in , 0, sizeof(in));
	in.sin_family	= AF_INET;
	in.sin_port		= htons(nPort);
	in.sin_addr.S_un.S_addr	= inet_addr(szAddress);

	return hsendto(buf, len, (const sockaddr*)&in);
}