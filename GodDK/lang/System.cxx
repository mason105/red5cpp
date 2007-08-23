
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdio.h>
#include <time.h>
#include "lang/System.h"
#include "io/FileInputStream.h"
using goddk::io::FileInputStream;
#include "io/FileOutputStream.h"
using goddk::io::FileOutputStream;

using namespace goddk::lang;
#define td_milliseconds(val) (jlong(1000) * jlong(val))
#define td_seconds(val) td_milliseconds(jlong(val) * jlong(1000))
#define td_minutes(val) td_seconds(jlong(val) * jlong(60))
#define td_hours(val) td_minutes(jlong(val) * jlong(60))
#define td_days(val) td_hours(jlong(val) * jlong(24))
#define td_weeks(val) td_days(jlong(val) * jlong(7))
struct timezone 
{
	int tz_minuteswest;
	int tz_dsttime;
};
jlong TIME_FACTOR = (0x19db1ded53ea710);
jlong NSPERSEC = 10000000;


jlong
mm_to_clock_t(FILETIME* src, bool flag)
{
	jlong total = ((jlong) src->dwHighDateTime << 32) + (src->dwLowDateTime);
	if (flag == true)
		total -= TIME_FACTOR;
	total /= (jlong) (NSPERSEC / CLOCKS_PER_SEC);
	return total;
}

void
mm_totimeval(struct timeval *dst, FILETIME *src, int sub, bool flag)
{
	jlong x = mm_to_clock_t(src, flag);

	x *= (int) (1e6) / CLOCKS_PER_SEC; 
	x -= (jlong) sub * (int) (1e6);

	dst->tv_usec = long(x % (jlong) (1e6)); 
	dst->tv_sec = long(x / (jlong) (1e6));
}
int
mm_gettimeofday(struct timeval* p, 
struct timezone* z)
{
	int res = 0;
	DWORD tzid;
	TIME_ZONE_INFORMATION tz;
	LONG bias;
	tzid = GetTimeZoneInformation (&tz);
	if (tzid == TIME_ZONE_ID_INVALID)
		res = -1;
	if (tzid == TIME_ZONE_ID_DAYLIGHT)
		bias = tz.Bias + tz.DaylightBias;
	else
		bias = tz.Bias + tz.StandardBias;

	if (p != NULL) {
		SYSTEMTIME t;
		FILETIME f;
		GetSystemTime(&t);
		if (SystemTimeToFileTime(&t, &f) == FALSE)
			res = -1;
		mm_totimeval(p, &f, 0, 1);
	}

	if (z != NULL) {
		z->tz_minuteswest = bias;
		z->tz_dsttime = (tzid == TIME_ZONE_ID_DAYLIGHT);
	}
	return res;
}

jlong System::currentTimeMillis()
{
	struct timeval time;
	mm_gettimeofday(&time, 0);
	int _seconds;
	int _useconds;
	_seconds = time.tv_sec;
	_useconds = time.tv_usec;

	jlong lTickCount = (jlong(_seconds) * jlong(1000)) + jlong(_useconds) / jlong(1000);

	return lTickCount;
}

//	FileInputStream  fin(stdin);
//	FileOutputStream fout(stdout);
//	FileOutputStream ferr(stderr);

//	PrintStream pout(fout);
//	PrintStream perr(ferr);
//InputStream& System::in = fin;
//PrintStream& System::out = pout;
//PrintStream& System::err = perr;
