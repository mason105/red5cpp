/*********************************************************************\
	FILE:		RC6.H
	DATE:		Aug. 15, 1999
	AUTHOR:		Chen Longsen
	Description:		
\*********************************************************************/

#define RC6W unsigned long 		
#define lgW	5					
#define const_r	20				
#define const_b 16				
#define P32 0xB7E15163l			
#define Q32 0x9E3779B9l			

#define Improper_Text_Length	1

typedef struct _RC6_KEY
{
	char Signature[4];		
	unsigned long Length;	
	RC6W SKey[2*const_r+4];
} RC6_KEY, * PRC6_KEY;

extern void GenerateKey(void * bRand,PRC6_KEY);
extern unsigned long EncryptData(RC6_KEY * hKey, unsigned char* PlainText, unsigned long TextLen, unsigned char* CipherText);
extern unsigned long DecryptData(RC6_KEY * hKey, unsigned char* CipherText, unsigned long TextLen, unsigned char* PlainText);
