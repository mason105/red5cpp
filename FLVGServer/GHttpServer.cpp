#include "stdafx.h"
#include ".\ghttpserver.h"

int uhMpd(UrlHandlerParam* param);
int ehMpd(MW_EVENT msg, void* arg);
int uhStats(UrlHandlerParam* param);
int uhWebCounter(UrlHandlerParam* param);
int uhVod(UrlHandlerParam* param);
int uhVodStream(UrlHandlerParam* param);
int ehVod(MW_EVENT msg, void* arg);
int uhTest(UrlHandlerParam* param);

UrlHandler urlHandlerList[]={
	{"~stats",uhStats,NULL},
#ifdef _MPD
	{"mplayer/",uhMpd,ehMpd},
#endif
#ifdef _VOD
	{"vod/",uhVod,ehVod},
	{"vodstream.avi",uhVodStream,NULL},
#endif
	{NULL},
	{NULL},
};



const char *pageHead="<html><body class='body'><table border=1 cellpadding=0 cellspacing=0 width=280 class='body'>";
const char *pageCellBegin="<tr><td width=140>%s</td><td width=140>";
const char *pageCellEnd="</td></tr>";
const char *pageTail="</body></html>";


int uhStats(UrlHandlerParam* param)
{
	 char *p;
	char buf[30];
	HttpStats *stats=&((HttpParam*)param->hp)->stats;
	HttpRequest *req=&param->hs->request;
	int ret=FLAG_DATA_RAW;

	mwGetHttpDateTime(time(NULL),buf);

	if (stats->clientCount>4) {
		param->pucBuffer=(char*)malloc(stats->clientCount*256+1024);
		ret=FLAG_DATA_RAW | FLAG_TO_FREE;
	}

	p=param->pucBuffer;
	//generate page
	p+=sprintf(p,pageHead);

	p+=sprintf(p,pageCellBegin,"Your IP address:");
	p+=sprintf(p,"%d.%d.%d.%d%s",
		req->ipAddr.caddr[3],
		req->ipAddr.caddr[2],
		req->ipAddr.caddr[1],
		req->ipAddr.caddr[0],
		pageCellEnd);

	p+=sprintf(p,pageCellBegin,"Current time:");
	p+=sprintf(p,"%s%s",buf,pageCellEnd);

	p+=sprintf(p,pageCellBegin,"Server uptime:",time(NULL)-stats->startTime);
	p+=sprintf(p,"%d sec(s)%s",time(NULL)-stats->startTime,pageCellEnd);

	p+=sprintf(p,pageCellBegin,"Connected clients:");
	p+=sprintf(p,"%d%s",stats->clientCount,pageCellEnd);

	p+=sprintf(p,pageCellBegin,"Maximum clients:");
	p+=sprintf(p,"%d%s",stats->clientCountMax,pageCellEnd);

	p+=sprintf(p,pageCellBegin,"Requests:");
	p+=sprintf(p,"%d%s",stats->reqCount,pageCellEnd);

	p+=sprintf(p,pageCellBegin,"Files sent:");
	p+=sprintf(p,"%d%s",stats->fileSentCount,pageCellEnd);

	p+=sprintf(p,pageCellBegin,"Bytes sent:");
	p+=sprintf(p,"%d bytes%s</table>",stats->fileSentBytes,pageCellEnd);

	p+=sprintf(p,"<br>Connected peers:<hr>");
	{
		HttpSocket *phsSocketCur;
		time_t curtime=time(NULL);
		for (phsSocketCur=((HttpParam*)param->hp)->phsSocketHead; phsSocketCur; phsSocketCur=phsSocketCur->next) {
			IP ip=phsSocketCur->request.ipAddr;
			p+=sprintf(p,"<br>Socket %d: %d.%d.%d.%d / Reqs: %d / Expire in %d ",
				phsSocketCur->socket,ip.caddr[3],ip.caddr[2],ip.caddr[1],ip.caddr[0],phsSocketCur->iRequestCount,phsSocketCur->tmExpirationTime-curtime);
			if (phsSocketCur->request.pucPath)
				p+=sprintf(p,"(%d/%d)",phsSocketCur->response.iSentBytes,phsSocketCur->response.iContentLength);
			else
				p+=sprintf(p,"(idle)");
		}
	}

	p+=sprintf(p,pageTail);

	//return data to server
	param->iDataBytes=(int)p-(int)(param->pucBuffer);
	param->fileType=HTTPFILETYPE_HTML;
	return ret;
}

#define TOTAL_COUNTERS 8
static unsigned long counter[TOTAL_COUNTERS];
char *pchCounterFile=NULL;

void saveWebCounter()
{
	int fd;
	if (!pchCounterFile) return;
	printf("Saving counter data...\n");
	fd=open(pchCounterFile,O_WRONLY|O_CREAT);
	if (fd<=0) return;
	write(fd,counter,sizeof(counter));
	close(fd);
}

int loadWebCounter()
{
	int fd;
	memset(&counter,0,sizeof(counter));
	if (!pchCounterFile) return -1;
	fd=open(pchCounterFile,O_RDONLY);
	if (fd<=0) {
		return -1;
	}
	read(fd,counter,sizeof(counter));
	close(fd);
	return 0;
}

int itoc(int num, char *pbuf, int type)
{
	static const char *chNum[]={"零","一","二","三","四","五","六","七","八","九"};
	static const char *chUnit[]={"亿","万","千","百","十","",NULL};
	char *p=pbuf;
	int c=1000000000,unit=4,d,last=0;
	if (num==0) return sprintf(pbuf,chNum[0]);
	if (num<0) {
		p+=sprintf(pbuf,"负");
		num=-num;
	}
	d=num;
	for (;;) {
		do {
			int tmp=d/c;
			if (tmp>0) {
				p+=sprintf(p,"%s%s",(unit==2 && tmp==1)?"":chNum[tmp],chUnit[unit]);
				d%=c;
			} else if (last!=0 && c>=10 && d>0) {
				p+=sprintf(p,chNum[0]);
			}
			last=tmp;
			c/=10;
		} while(chUnit[++unit]);
		if (c==0) break;
		if (c==1000 && num>=10000)
			p+=sprintf(p,chUnit[1]);
		else if (c==10000000 && num>=100000000)
			p+=sprintf(p,chUnit[0]);
		unit=2;
	}
	return (int)(p-pbuf);
}

int uhWebCounter(UrlHandlerParam* param)
{
	static int visitCount=0;
	int idx,mode=0;
	char *p;

	p=strchr(param->pucRequest,'&');
	if (p) {
		*(p++)=0;
		if (GETDWORD(p)==DEFDWORD('m','o','d','e')) {
			mode=atoi(p+5);
		}
	}
	p=strchr(param->pucRequest,'=');
	if (p) *p=0;
	idx=atoi(param->pucRequest);
	if (idx>=TOTAL_COUNTERS) return 0;
	counter[idx]++;
	if (p) counter[idx]=atoi(p+1);
	p=param->pucBuffer;
	if ((mode & 4)==0) {
		p+=sprintf(p,"document.write('");
	}
	switch (mode & 3) {
	case 0:
		p+=sprintf(p,"%d",counter[idx]);
		break;
	case 1:
		p+=itoc(counter[idx],p,0);
		break;
	case 2:
		p+=itoc(counter[idx],p,1);
		break;
	}
	if ((mode & 4)==0) {
		p+=sprintf(p,"');");
	}
	param->iDataBytes=(int)p-(int)param->pucBuffer;

	param->fileType=HTTPFILETYPE_TEXT;
	if (((++visitCount) & 0xf)==0) {
		saveWebCounter();
	}
	return FLAG_DATA_RAW;
}


int DefaultWebSubstCallback(SubstParam* sp)
{
	
	if (!strcmp(sp->pchParamName,"mykeyword")) {
		return sprintf(sp->pchParamValue, "%d", time(NULL));
	}
	return -1;
}


int DefaultWebPostCallback(PostParam* pp)
{
	int iReturn=WEBPOST_OK;


	strcpy(pp->chFilename,"index.htm");

	return iReturn;
}


int DefaultWebFileUploadCallback(char *pchFilename,
								 OCTET oFileuploadStatus,
								 OCTET *poData,
								 DWORD dwDataChunkSize)
{
	
	return 0;
}


GHttpServer::GHttpServer(void)
{
	_running = false;
}

GHttpServer::~GHttpServer(void)
{
}
BOOL	GHttpServer::Start(int nPort, char* szWebPath)
{
	if(_running)
		return TRUE;
	memset(&httpParam,0,sizeof(HttpParam));
	httpParam.maxClients=32;
	httpParam.httpPort=nPort;
	httpParam.maxReqPerConn=99;
	httpParam.pchWebPath=strdup(szWebPath);
	httpParam.pxUrlHandler=urlHandlerList;
	httpParam.flags=FLAG_DIR_LISTING;
	
	httpParam.pfnSubst=DefaultWebSubstCallback;

	if(mwServerStart(&httpParam) == 0)
	{
		_running = true;
		return TRUE;
	}
	else
	{
		Stop();
		return FALSE;
	}
}
void	GHttpServer::Stop()
{
	if(!_running)
		return;
	MiniWebQuit(0);
	mwServerShutdown(&httpParam);
	free(httpParam.pchWebPath);
}
int GHttpServer::MiniWebQuit(int arg) {
	httpParam.bKillWebserver=1;
	return 0;
}