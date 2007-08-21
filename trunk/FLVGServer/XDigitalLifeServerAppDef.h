#ifndef _XDigitalLifeServerAppDef_H
#define _XDigitalLifeServerAppDef_H
#include <list>
using namespace std;
#undef  LANG_CHINESE
#ifdef LANG_CHINESE
#define STR_ServerPerfomance		"性能"
#define STR_PublishPoint			"发布点"
#define STR_VODFiles				"点播文件"
#define STR_Relay					"转发"
#define STR_Connection				"连接"
#define STR_Setting					"设置"
#define STR_Log						"日志"
#else
#define STR_ServerPerfomance		"Perfomance"
#define STR_PublishPoint			"Publish Point"
#define STR_VODFiles				"VOD Files"
#define STR_Relay					"Relay"
#define STR_Connection				"Connection"
#define STR_Setting					"Setting"
#define STR_Log						"Log"
#endif

#define WM_CONTROLPROPERTIESTREE_SELECTED	WM_USER + 100
#define MRL_MRURegKey		_T("XDigitalServer MRL MRU")
#define MRL_MRUValueFormat	 _T("File #%d")

#define TIMERID_ONESECOND			1001
#define TIMERID_TWOSECOND			1002
enum RelayType{
	RelayType_Broadcast,
	RelayType_Web,
};
typedef struct XDLS_RelayPoint_t
{
	CString			strName;
	CString			strInput;
	RelayType		rt;
	//for broadcast
	CString				strNetProcotol;
	CString				strEncapsulationMedthod;
	CString				strNetAddress;
	CString				strMifaceAddress;
	DWORD				dwNetNetPort;
	DWORD				dwNetRTSPPort;
	//for p2p
	CString				strWebSourceType;
	CString				strWebDescription;
	CString				strWebRelayID;
	DWORD				dwWebRelayBitrate;
	
	void*				pRelayPoint;
}XDLS_RelayPoint, *LPXDLS_RelayPoint;
typedef list<XDLS_RelayPoint*>	RELAY_LIST;
typedef RELAY_LIST::iterator		RELAY_LIST_IT;

typedef struct XDLS_Setting_t
{
	char		szServerAddress[64];
	int			nServerPort;
	
	char		szVODFilePath[512];

	int			nWebServerPort;
	int			nWebMaxOutputBitrate;
	int			nWebMaxRelays;

	RELAY_LIST	RelayList;
}XDLS_Setting, *LPXDLS_Setting;


const int Frame_Height	= 18;


#endif//_XDigitalLifeServerAppDef_H