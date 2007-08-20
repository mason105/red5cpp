
//**********************************************************************************
//
// Filename: vixstypes.h
//
// ViXS Systems Confidential and Proprietary
//
//*********************************************************************************

#ifndef _VIXSTYPES_H_
#define _VIXSTYPES_H_

// Our base data types are defined in following flatform dependent files
// The data types are:
//  int8    - 8-bit integer
//  uint8   - 8-bit unsigned integer
//  int16   - 16-bit integer
//  uint16  - 16-bit unsigned integer
//  int32   - 32-bit integer
//  uint32  - 32-bit unsigned integer
//  int64   - 64-bit integer
//  uint64  - 64-bit unsigned integer
//  pint8   - pointer to 8-bit integer
//  puint8  - pointer to 8-bit unsigned integer
//  pint16  - pointer to 16-bit integer
//  puint16 - pointer to 16-bit unsigned integer
//  pint32  - pointer to 32-bit integer
//  puint32 - pointer to 32-bit unsigned integer
//  pint64  - pointer to 64-bit integer
//  puint64 - pointer to 64-bit unsigned integer
//
//  uint    - unsigned integer (flatform native)
//  puint   - pointer to unsigned integer (flatform native)
//
//  pvoid   - pointer to void
//

#ifdef _WIN64   // Windows 64-bit OS

typedef __int64             int32_ptr, *pint32_ptr;
typedef unsigned __int64    uint32_ptr, *puint32_ptr;
typedef __int64             int_ptr, *pint_ptr;
typedef unsigned __int64    uint_ptr, *puint_ptr;
typedef __int64             long_ptr, *plong_ptr;
typedef unsigned __int64    ulong_ptr, *pulong_ptr;

#define PAGE_TABLE_MASK     0xFFFFFFFFFFFFF000
#define PAGE_MASK           0x0000000000000FFF
#define ADDRESS_MINUS_ONE   0xFFFFFFFFFFFFFFFF

#else // _WIN32 or Linux32 or other 32-bit OS

typedef int                 int32_ptr, *pint32_ptr;
typedef unsigned int        uint32_ptr, *puint32_ptr;
typedef int                 int_ptr, *pint_ptr;
typedef unsigned int        uint_ptr, *puint_ptr;
typedef long                long_ptr, *plong_ptr;
typedef unsigned long       ulong_ptr, *pulong_ptr;

#define PAGE_TABLE_MASK     0xFFFFF000

#ifndef PAGE_MASK
#define PAGE_MASK           0x00000FFF
#endif

#define ADDRESS_MINUS_ONE   0xFFFFFFFF

#endif

typedef unsigned char       uint8, *puint8;
typedef signed char         int8, *pint8;
typedef unsigned short      uint16, *puint16;
typedef signed short        int16, *pint16;
typedef unsigned long       uint32, *puint32;
typedef signed long         int32, *pint32;
typedef unsigned int        *puint;
typedef signed int          *pint;
typedef void                *pvoid;
typedef volatile uint32     *pvuint32;


#if (!defined(WIN32) || !defined(_BASETSD_H_)) && (!defined(_WIN32_WCE))
typedef unsigned char       UINT8, *PUINT8;
typedef signed char         INT8, *PINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef signed short        INT16, *PINT16;
typedef unsigned long       UINT32, *PUINT32;
typedef signed long         INT32, *PINT32;
typedef unsigned int        UINT, *PUINT;
typedef signed int          INT, *PINT;
typedef void                *PVOID;
#endif

#ifdef _WIN32_WCE
typedef unsigned __int64    uint64, *puint64;
typedef signed __int64      int64, *pint64;
#endif

#ifdef WIN32
typedef unsigned __int64    uint64, *puint64;
typedef signed __int64      int64, *pint64;
#if !defined(WIN32) || !defined(_BASETSD_H_)
typedef unsigned __int64    UINT64, *PUINT64;
typedef signed __int64      INT64, *PINT64;
#endif
#endif

#ifdef linux_gnu
typedef unsigned long long  uint64, *puint64;
typedef signed long long    int64, *pint64;
typedef unsigned long long  UINT64, *PUINT64;
typedef signed long long    INT64, *PINT64;
#endif



#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif
#ifndef NULL
#define NULL    ((void*)0)
#endif

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // VIXSTYPES_H

