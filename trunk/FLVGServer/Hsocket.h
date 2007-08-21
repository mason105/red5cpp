#pragma once

#include <winsock2.h>
#pragma comment(lib,"WS2_32.lib")
#include <string>
using namespace std;

class CHsocket
{
public:
	CHsocket(void);
	CHsocket(SOCKET socket);
	CHsocket(CHsocket& hsocket);
	~CHsocket(void);

private:
	SOCKET m_socket;
	struct sockaddr_in m_sockaddr;
	struct sockaddr_in m_sendsockaddr;
	string m_straddr;//local host address ro remote host address

public:
	static bool StartSock(void);//Init socket
	bool		hsocket(unsigned int port = 0, int type = SOCK_STREAM, const char* address = NULL);//create a socket, if port not zero, then call bind function.
	int			hlisten(int backlog);
	int			hconnect(char* address, unsigned int port);
	int			hsend(const char* buf, int len);
	int			hrecv(char* buf, int len);
	SOCKET		haccept(void);
	int			hclosesocket(void);
	static int  CleanSock(void);
	SOCKET		operator *(void); 
	CHsocket&	operator =(CHsocket& hsocket);

	// udp 
	int hsendto(const char* buf, int len, const sockaddr* to);
	int hsendto(const char* buf, int len);
	int hrecvfrom(char* buf, int len, sockaddr* from);
	int hrecvfrom(char* buf, int len);

//extend function
public:
	void		setsocket(SOCKET socket);
	void		setsocket(CHsocket& hsocket);
	SOCKET		getsocket(void) const;
	void		makesendsockaddr(const char* ipaddr, unsigned int port, short family = AF_INET, const char* sin_zero = NULL);//if ipaddr is null, bind ip to INADDR_ANY
	const char* getsockaddr(bool brecvsock = true);
	unsigned int getsockport(bool brecvsock = true);
	int			getremoteport(void);
	int			getlocalport(void);
	const char* getremoteaddr(void);
	const char* getlocaladdr(void);
	bool		islocalip(const char* ip);
};

