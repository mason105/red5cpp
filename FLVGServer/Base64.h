// Base64.h: interface for the CBase64 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE64_H__9F9A4FBF_E43F_49B7_A05E_3A483C6B3A22__INCLUDED_)
#define AFX_BASE64_H__9F9A4FBF_E43F_49B7_A05E_3A483C6B3A22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBase64  
{
public:
	 char GetB64Char(int index);
	 int GetB64Index(char ch);
	 int Base64Decode(char *buf,const char* base64code,int src_len=0);
	 int Base64Encode(char* base64code,const char* src,int src_len=0);
	CBase64();
	virtual ~CBase64();

};

#endif // !defined(AFX_BASE64_H__9F9A4FBF_E43F_49B7_A05E_3A483C6B3A22__INCLUDED_)
