#pragma once
#include <stdio.h>
#include <string.h>
extern "C"
{
#include "httppil.h"
#include "httpapi.h"
#include "revision.h"
}
class GHttpServer
{
public:
	GHttpServer(void);
	~GHttpServer(void);

	BOOL	Start(int nPort, char* szWebPath);
	void	Stop();

protected:
	int MiniWebQuit(int arg);
protected:
	HttpParam httpParam;
	bool	  _running;
};
