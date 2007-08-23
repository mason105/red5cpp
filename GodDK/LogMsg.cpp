#include ".\logmsg.h"
#include <string>
#include <cstring>
#include <stdio.h>
#include <winsock2.h>

#define BUFFER_SIZE 8192

static const char hexchars[]="0123456789abcdef";
unsigned char *
hexify(unsigned char *p, const unsigned char *s, int length, bool ascii) 
{

	unsigned char *p1 = p;

	// convert some characters so it'll look right in the log
	for (int i=0 ; i<length; i++) {
		// use the hex value
		if (isprint(s[i]) && ascii) {
			if (i>1) {
				if (!isprint(s[i-1])) {
					*p++ = ' ';
				}
			}
			*p++ = s[i];
			if (!isprint(s[i+1])) {
				*p++ = ' ';
			}
		} else {
			*p++ = hexchars[s[i] >> 4];
			*p++ = hexchars[s[i] & 0xf];
		}
	}

	*p = '\0';

	return p1;
}
void
log_msg(const char* fmt, ...)
{
//#ifndef _DEBUG
//	return;
//#else
	va_list ap;
	char tmp[BUFFER_SIZE];

	va_start (ap, fmt);
	_vsnprintf (tmp, BUFFER_SIZE, fmt, ap);
	tmp[BUFFER_SIZE-1] = '\0';

	printf("%s\n", tmp);

	va_end (ap);
//#endif

}
void
log_dump(const char* fmt, int len)
{
//#ifndef _DEBUG
//	return;
//#else
	unsigned char tmp[BUFFER_SIZE];
	hexify(tmp, (const unsigned char *)fmt, len, true);
	printf((char*)tmp);
//#endif
}
