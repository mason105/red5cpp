#include "stdafx.h"
#include ".\hsocket.h"

CHsocket::CHsocket(CHsocket& hsocket) : m_socket(hsocket.m_socket)
{

}

CHsocket::CHsocket(SOCKET socket) : m_socket(socket)
{

}

CHsocket::CHsocket()
{
	m_socket = INVALID_SOCKET;
}

CHsocket::~CHsocket()
{
}

bool CHsocket::StartSock()
{
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(ret == SOCKET_ERROR)
	{
	//	cout << "ÍøÂç³õ»¯Ê§°Ü" << endl;	
		return false;
	}

	return true;
}

bool CHsocket::hsocket(unsigned int port, int type, const char* address)
{
	m_socket = socket(AF_INET, type, 0);
	if(m_socket == SOCKET_ERROR)
	{
	//	cout << "socket error" << endl;
		return false;
	}

	if(port == 0)// if nPort is zero, only create a socket, not bind
		return true;

	makesendsockaddr(address, port);

	int ret = bind(m_socket, (struct sockaddr*)&m_sendsockaddr, sizeof(m_sendsockaddr));
	if(ret == SOCKET_ERROR)
	{
	//	cout << "bind error" << endl;
		return false;
	}

	return true;
}

int CHsocket::hconnect(char* address, unsigned int port)
{
	struct sockaddr_in sockaddr;
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_addr.s_addr	= inet_addr(address);
	sockaddr.sin_family		= AF_INET;
	sockaddr.sin_port			= htons(port);
	return connect(m_socket, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
}

int CHsocket::hlisten(int backlog)
{
	return listen(m_socket, backlog);
}

SOCKET CHsocket::haccept()
{
	struct sockaddr_in sockaddr;
	int	addrlen = sizeof(sockaddr);

	memset(&sockaddr, 0, sizeof(sockaddr));

	return accept(m_socket, (struct sockaddr*)&sockaddr, &addrlen);
}

int CHsocket:: hsend(const char* buf, int len)
{
	return send(m_socket, buf, len, 0);
}

int CHsocket::hrecv(char* buf, int len)
{
	return recv(m_socket, buf, len, 0);
}

int CHsocket::hsendto(const char* buf, int len, const sockaddr* to)
{
	return sendto(m_socket, buf, len, 0, to, sizeof(m_sockaddr));
}

int CHsocket::hsendto(const char* buf, int len)
{
	return sendto(m_socket, buf, len, 0, (struct sockaddr*)&m_sendsockaddr, sizeof(m_sendsockaddr));
}

int CHsocket::hrecvfrom(char* buf, int len, sockaddr* from)
{
	int sockaddrlen = sizeof(m_sockaddr);
	
	return recvfrom(m_socket, buf, len, 0, from, &sockaddrlen);
}

int CHsocket::hrecvfrom(char* buf, int len)
{
	int sockaddrlen = sizeof(m_sockaddr);

	return recvfrom(m_socket, buf, len, 0, (struct sockaddr*)&m_sockaddr, &sockaddrlen);
}

int CHsocket::hclosesocket()
{
	return closesocket(m_socket);
}

int CHsocket::CleanSock()
{
	return WSACleanup();
}

SOCKET CHsocket::operator *()
{
	return m_socket; 
}

CHsocket& CHsocket::operator =(CHsocket& hsocket)
{
	if(this == &hsocket)
		return *this;

	m_socket = hsocket.m_socket;
	memcpy(&m_sockaddr, &hsocket.m_sockaddr, sizeof(m_sockaddr));
	memcpy(&m_sendsockaddr, &hsocket.m_sendsockaddr, sizeof(m_sendsockaddr));
	m_straddr = hsocket.m_straddr;
	return *this;
}

void CHsocket::makesendsockaddr(const char* ipaddr, unsigned int port, short family, const char* sin_zero)
{
	memset(&m_sendsockaddr, 0, sizeof(m_sendsockaddr));

	m_sendsockaddr.sin_addr.s_addr	= (ipaddr == NULL) ? htonl(INADDR_ANY) : inet_addr(ipaddr);
	m_sendsockaddr.sin_family		= family;
	m_sendsockaddr.sin_port			= htons(port);
}

const char* CHsocket::getsockaddr(bool brecvsock)
{
	if(brecvsock)
		m_straddr = inet_ntoa(m_sockaddr.sin_addr);
	else
		m_straddr = inet_ntoa(m_sendsockaddr.sin_addr);

	return m_straddr.data();
}

unsigned int CHsocket::getsockport(bool brecvsock)
{
	if(brecvsock)
		return ntohs(m_sockaddr.sin_port);

	return ntohs(m_sendsockaddr.sin_port);
}

const char* CHsocket::getremoteaddr()
{
	struct sockaddr_in sockaddr;
	int nlen = sizeof(sockaddr);

	memset(&sockaddr, 0, sizeof(sockaddr));

	getpeername(m_socket, (struct sockaddr*)&sockaddr, &nlen);

	m_straddr = inet_ntoa(sockaddr.sin_addr);

	return m_straddr.data();
}

const char* CHsocket::getlocaladdr()
{
	int ret;
	struct sockaddr_in sockaddr;
	int nlen = sizeof(sockaddr);

	memset(&sockaddr, 0, sizeof(sockaddr));

	ret = getsockname(m_socket, (struct sockaddr*)&sockaddr, &nlen);
	if(ret == SOCKET_ERROR)
	{
		struct hostent* phost;
		char szname[128];
		gethostname(szname, sizeof(szname));
		phost = gethostbyname(szname);

		m_straddr = inet_ntoa(*(in_addr*)phost->h_addr_list[0]);
	}
	else
	{
		m_straddr = inet_ntoa(sockaddr.sin_addr);
	}

	return m_straddr.data();
}

int CHsocket::getremoteport()
{
	struct sockaddr_in sockaddr;
	int nlen = sizeof(sockaddr);

	memset(&sockaddr, 0, sizeof(sockaddr));

	getpeername(m_socket, (struct sockaddr*)&sockaddr, &nlen);

	return ntohs(sockaddr.sin_port);
}

int CHsocket::getlocalport()
{
	struct sockaddr_in sockaddr;
	int nlen = sizeof(sockaddr);

	memset(&sockaddr, 0, sizeof(sockaddr));

	getsockname(m_socket, (struct sockaddr*)&sockaddr, &nlen);
	
	return ntohs(sockaddr.sin_port);	
}

void CHsocket::setsocket(SOCKET socket)
{
	m_socket = socket;
}

void CHsocket::setsocket(CHsocket& hsocket)
{
	m_socket = *hsocket;
}

SOCKET CHsocket::getsocket() const
{
	return m_socket;
}

bool CHsocket::islocalip(const char* ip)
{
	string strip(ip);
	if((int)strip.find("192.168") == 0)
		return true;

	return false;
}