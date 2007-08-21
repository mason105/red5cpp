#ifndef DOG_H
#define DOG_H
#include "windows.h"
#include "Md5.h"
#include "Rc6.h"
#include "time.h"

enum CommandType{dog_attestation=1,dog_read,dog_write};
enum AuthType{rc6=1,md5};

typedef struct _DL_DLL_PARA
{
	DWORD    Command;         //[in]������
	LPVOID   lpDogParam;      //[in]ָ��DOG_PARA�ṹ��ָ��
	LPVOID   lpAuthParam;     //[in]ָ��AUTH_PARA�ṹ��ָ��
	
}DL_DLL_PARA, * PDL_DLL_PARA;

typedef struct _DOG_PARA
{
	USHORT	DogAddr;     //[in]�׵�ַ
	USHORT	DogBytes;    //[in]�����ֽ���
	BYTE	DogData[100];//[in][out]�����������
}DOG_PARA, * PDOG_PARA;

typedef struct _AUTH_PARA
{
	DWORD	Type;	      //[in]�㷨ѡ��Ŀǰֻ֧��rc6 ��ֻ��Ϊ1
	DWORD	Length;	      //[in]���ݳ��ȣ���rc6�㷨��ֻ��Ϊ16
	PUCHAR	pRandom;      //[in]�����16�ֽ������ָ��
	PUCHAR	pReturnRandom;//[out]����ļ�������ָ��
}AUTH_PARA, * PAUTH_PARA;
typedef unsigned long ( * RC_DLDOG)(PDL_DLL_PARA pDLLParam);
class CDog
{
public:
	CDog();
	~CDog();
	BOOL Init();
	BOOL WriteDog(int start,int len,char* content);
	BOOL ReadDog(int start,int len,char* result);
	void SetCommand(UINT nCommand);
	void SetRc6(BOOL use);
	BOOL IsRc6();
private:
	PDL_DLL_PARA	m_pDllPara;
	PDOG_PARA		m_pDogPara;
	PAUTH_PARA		m_pAuthPara;
	RC_DLDOG		RC_DLDog;
	int KeyLen;
	RC6_KEY RC6Key;
	//MD5  md5object;
	UCHAR    sign[16];   
	int RandomLen;
	HRESULT hresult;
	unsigned char Random[16];
	unsigned char DecryptRandom[16];
	unsigned char ReturnRandom[16];
};
#endif