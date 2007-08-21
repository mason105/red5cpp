/***********************************************************************
SafeNet China Ltd.

Filename:

    md5.h 

Description:

     Head file of  MD5  and HMAC_MD5 algorithms

Enviroment:

    C++ language

Developer:

	Mengxh

Date:

    2000.4.7

***********************************************************************/
#include <windows.h>

#if !defined(MD5_HPP)
#define MD5_HPP

/*#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef PUCHAR
#define PUCHAR unsigned char *
#endif

#ifndef PCHAR
#define PCHAR  char *
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef UINT
#define UINT unsigned int
#endif

#ifndef INT
#define INT int
#endif
*/


class MD5
{
private:
	ULONG	state[4];
	ULONG	count[2];
	UCHAR	buffer[64];
	ULONG	Key1[4], Key2[4];

	void	Init();
	void	Update(PUCHAR input, UINT inputLen);
	void	Final(unsigned char [16]);
	void	Transform(unsigned char [64]);
	void	Encode(unsigned char *, ULONG *, unsigned int);
	void	Decode(ULONG *, unsigned char *, unsigned int);
	void	Memcpy(PUCHAR, PUCHAR, unsigned int);
	void	Memset(PUCHAR, int, unsigned int);
public:
	MD5();
	void	SetKey(PCHAR key, int Length);
	void	HmacMd5(PCHAR text, INT text_len, PCHAR key, INT key_len, PUCHAR outBuf);
	void	HmacMd5(PCHAR text, INT text_len, PCHAR key, PUCHAR outBuf);
	void	HmacMd5(PCHAR text, PCHAR key, INT key_len, PUCHAR outBuf);
	void	HmacMd5(PCHAR text, PCHAR key, PUCHAR outBuf);
	void	HmacMd5(PCHAR text, INT text_len, PUCHAR outBuf);
	void	HmacMd5(PCHAR text, PUCHAR outBuf);
	void	Encrypt(PCHAR text, INT text_len, PUCHAR outBuf);
	void	Encrypt(PCHAR text, PUCHAR outBuf);
};

#endif
//
/***********************************************************************
    Init()
	Function description:
	  Initializing function of MD5 algorithm
***********************************************************************/
/***********************************************************************
   Update (PUCHAR input,	UINT inputLen)
   Function description:
	 Data update function of MD5 algorithm
***********************************************************************/
/***********************************************************************
   Final(unsigned char digest[16])
   Function description:
	 Operation function of MD5 algorithm
***********************************************************************/
/***********************************************************************
   SetKey(PCHAR key, int length)
   Function description:
	  Set the key of HMAC-MD5 algorithm
***********************************************************************/
/**************************************************************************************
  HmacMd5(PCHAR text, INT text_len, PUCHAR outBuf)
  Function description:
     Change the inputing data HMAC-MD5 algorithm using the key,put the result in outBuf
***************************************************************************************/
/***********************************************************************
  Encrypt(PCHAR text, INT text_len, PUCHAR outBuf)
  Function description:
	  Change the input data with MD5 algorithm, put the result in outBuf
***********************************************************************/
/**************************************************************************************
  HmacMd5(PCHAR text, INT text_len, PCHAR key, INT key_len, PUCHAR outBuf)
  Function description:
     Change the inputing data HMAC-MD5 algorithm using the key,put the result in outBuf
***************************************************************************************/
/***********************************************************************
  Transform(unsigned char block[64])
  Function description:
    Basic change function of MD5 algorithm
***********************************************************************/
/***********************************************************************
  Encode(unsigned char * output,	ULONG * input, unsigned int len)
  Function description:
    Change the input ULONG array to UCHAR array
***********************************************************************/
/***********************************************************************
  Decode(ULONG * output, unsigned char * input, unsigned int len)
  Function description:
    Change the input ULONG array to UCHAR array
***********************************************************************/
/***********************************************************************
  Memcpy(PUCHAR output, PUCHAR input, unsigned int len)
  Function description:
    Memory copy function
***********************************************************************/
/***********************************************************************
  Memset(PUCHAR output, int value, unsigned int len)
  Function description:
    Memory set function
***********************************************************************/
