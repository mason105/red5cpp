#include "StdAfx.h"
#include "Dog.h"


unsigned char Key[6]={'a','b','c','d','e','f'};
char Md5Key[12]={'1','3','2','4','3','5','4','6','5','7','6','8'};
CDog::CDog()
{
	RC_DLDog = NULL;
	m_pDogPara = NULL;
	m_pDllPara = NULL;
	m_pAuthPara = NULL;
}
BOOL CDog::Init()
{
	m_pDllPara = new DL_DLL_PARA;
	m_pAuthPara = new AUTH_PARA;
	m_pDogPara = new DOG_PARA;

	m_pDllPara->lpAuthParam = m_pAuthPara;
	m_pDllPara->lpDogParam = m_pDogPara;
	
	if(!m_pAuthPara || !m_pDllPara || !m_pDogPara)
		return FALSE;
	
// --------------------------------------------- [3/16/2007]
	RandomLen = 16;
	KeyLen = 6;
	HINSTANCE hLib;
	hLib = LoadLibrary(TEXT("win32hdll.dll"));
	if(hLib != NULL)
	{
		RC_DLDog =(RC_DLDOG)::GetProcAddress((HMODULE)hLib,"RC_DLDog");
	}
	else
	{
		return FALSE;
	}

// ---------------------------------------------- [3/16/2007]
   
	memset(sign,0,16);
	memset(Random,0,16);
	memset(DecryptRandom,0,16);
	memset(ReturnRandom,0,16);
	
	srand((unsigned)time(NULL));
	for (int i=0;i<8;i++)
	{
		*(int *)&Random[2*i]=rand();
	}

	m_pAuthPara->Type = 1;
	m_pAuthPara->Length = 16;
	m_pAuthPara->pRandom = Random;
	m_pAuthPara->pReturnRandom = ReturnRandom;

	m_pDllPara->Command = 1;
	m_pDllPara->lpAuthParam = m_pAuthPara;

	hresult=RC_DLDog(m_pDllPara);
	if (hresult!=0)//check the retur value of Auth
	{
		return FALSE;
	}
	//enter Md5
	/*md5object.SetKey(Md5Key,12);//set MD5 key
    md5object.Encrypt((PCHAR)Key,KeyLen,sign);//hash a 16 bytes sign
	GenerateKey(sign,&RC6Key);//out the RC6 key
	DecryptData(&RC6Key,ReturnRandom,16,DecryptRandom);//decrypt the ReturnRandom
	
	for (int j=0;j<RandomLen;j++)//check the decrypt of random data
	{
		if (Random[j]!=DecryptRandom[j])
		{
			return FALSE;
		}
	}
	*/
	return  TRUE;
}
BOOL CDog::WriteDog(int start,int len,char* content)
{
	m_pDllPara->Command = dog_write;
	m_pDogPara->DogAddr = (USHORT) start;
	m_pDogPara->DogBytes = (USHORT) len;
	strcpy((char*)&m_pDogPara->DogData,content);
	int n = RC_DLDog(m_pDllPara);
	if(n)
		return FALSE;
	return TRUE;
}
BOOL CDog::ReadDog(int start,int len,char* result)
{
	m_pDllPara->Command = dog_read;
	m_pDogPara->DogAddr = (USHORT)start;
	m_pDogPara->DogBytes = (USHORT) len;
	
	if(RC_DLDog(m_pDllPara))
		return FALSE;
	else
	{
		strcpy(result,(char*)m_pDogPara->DogData);
		return TRUE;
	}
}

void CDog::SetCommand(UINT nCommand)
{
	m_pDllPara->Command = nCommand;
}

void CDog::SetRc6(BOOL use)
{

}
BOOL CDog::IsRc6()
{
	return TRUE;
}

CDog::~CDog()
{
	delete m_pDllPara;
	delete m_pDogPara;
	delete m_pAuthPara;
}