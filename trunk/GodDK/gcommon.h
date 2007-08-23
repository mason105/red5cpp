#pragma	  once

#define _REENTRANT

#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x0400
#endif
#include <windows.h>

#if __MWERKS__
# if __INTEL__
#  define WORDS_BIGENDIAN		0
# else
#  error Unknown CPU type in MetroWerks CodeWarrior
# endif
#elif defined(_MSC_VER)
# if defined(_M_IX86)
#  define WORDS_BIGENDIAN		0
#  define ROTL32(x, s) _rotl(x, s)
#  define ROTR32(x, s) _rotr(x, s)
# else
#  error Unknown CPU type in Microsoft Visual C
# endif
#else
# error Unknown compiler for WIN32
#endif

#if defined(_MSC_VER) || __MWERKS__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HAVE_ASSERT_H			1

#define HAVE_ERRNO_H			1
#define HAVE_CTYPE_H			1
#define HAVE_FCNTL_H			1
#define HAVE_TIME_H				1

#define HAVE_SYS_TYPES_H		0
#define HAVE_SYS_TIME_H			0

#define HAVE_THREAD_H			0
#define HAVE_SYNCH_H			0
#define HAVE_PTHREAD_H			0
#define HAVE_SEMAPHORE_H		0

#define HAVE_TERMIO_H			0
#define HAVE_SYS_AUDIOIO_H		0
#define HAVE_SYS_IOCTL_H		0
#define HAVE_SYS_SOUNDCARD_H	0

#define HAVE_GETTIMEOFDAY		0
#define HAVE_GETHRTIME			0

#define HAVE_DEV_TTY			0
#define HAVE_DEV_AUDIO			0
#define HAVE_DEV_DSP			0
#define HAVE_DEV_RANDOM			0
#define HAVE_DEV_URANDOM		0
#define HAVE_DEV_TTY			0

#else
#error Not set up for this compiler
#endif

#if __MWERKS__
#define HAVE_SYS_STAT_H			0

#define HAVE_LONG_LONG			1
#define HAVE_UNSIGNED_LONG_LONG	1

#define HAVE_64_BIT_INT			1
#define HAVE_64_BIT_UINT		1

#define SIZEOF_SIZE_T			4 /* not sure about this one */
#define SIZEOF_UNSIGNED_LONG	4

typedef char		int8_t;
typedef short		int16_t;
typedef long		int32_t;
typedef long long	int64_t;

typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned long		uint32_t;
typedef unsigned long long	uint64_t;

#elif defined(_MSC_VER)
#define HAVE_SYS_STAT_H			1

#define HAVE_LONG_LONG			0
#define HAVE_UNSIGNED_LONG_LONG	0

#define HAVE_64_BIT_INT			1
#define HAVE_64_BIT_UINT		1

#define SIZEOF_SIZE_T			4
#define SIZEOF_UNSIGNED_LONG	4

typedef signed char	int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed __int64 int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;

typedef long off_t;

#endif

#define MP_WBITS	32U

typedef HANDLE bc_cond_t;
typedef HANDLE bc_mutex_t;
typedef HANDLE bc_thread_t;
typedef DWORD  bc_threadid_t;



//////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) && !defined(WIN32)
# define WIN32 1
#endif

#if HAVE_ASSERT_H
# include <assert.h>
#else
# define assert(x)
#endif

#ifndef ROTL32
# define ROTL32(x, s) (((x) << (s)) | ((x) >> (32 - (s))))
#endif
#ifndef ROTR32
# define ROTR32(x, s) (((x) >> (s)) | ((x) << (32 - (s))))
#endif
#ifndef ROTR64
# define ROTR64(x, s) (((x) >> (s)) | ((x) << (64 - (s))))
#endif

typedef uint8_t		byte;


typedef int8_t		jbyte;
typedef int16_t		jshort;
typedef uint16_t	jushort;
typedef int32_t		jint;
typedef int64_t		jlong;
typedef wchar_t		jchar;
typedef float		jfloat;
typedef double		jdouble;

#if (MP_WBITS == 64)
typedef uint64_t	mpw;
typedef uint32_t	mphw;
#elif (MP_WBITS == 32)
# if HAVE_UINT64_T
#  define HAVE_MPDW 1
typedef uint64_t	mpdw;
# endif
typedef uint32_t	mpw;
typedef uint16_t	mphw;
#else
# error
#endif