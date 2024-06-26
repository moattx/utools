
/*
 * utools - power_netbsd.c
 * (C) 2023 moatx
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
*/


#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
/*
#include <unistd.h>
#include <sys/param.h>
#include <err.h>
#include <string.h>
*/

/*
#ifdef DEBUG
#define debug_print(fmt, ...) \
    fprintf(stderr, "%s: %d: %s(): debug: " fmt, \
        __FILE__, __LINE__, __func__, __VA_ARGS__)
#else
#define debug_print(fmt, ...) do {} while (0)
#endif
*/
/*
#define debug_print(fmt, ...)						\
        do { if (DEBUG) fprintf(stderr, "%s: %d: %s(): debug: " fmt, __FILE__,\
                                __LINE__, __func__, __VA_ARGS__); } while (0)
				*/

extern char *USAGE;

/* extern means definition is elsewhere(string.h) */
extern const char *__progname;

#ifndef __NetBSD__
static const char *
getprogname(void)
{
	return (__progname);
}
#endif

#ifdef __linux__
#if defined __GNUC__ || defined __clang__
#include <stdnoreturn.h>
_Noreturn
#endif
#endif
#ifdef __NetBSD__
__dead
#endif

static inline void
usage(int v)
{
	(void)fprintf(stderr, "usage: %s %s\n", getprogname(), USAGE);
	exit(v);
}

void rputs(double size);
void readfile (const char *path, char *rstr, size_t size);

/* #ifndef __BSD__ */
/*
#define _BSD_ __NetBSD__ || __OpenBSD__ || __FreeBSD__
*/
/*
#endif
*/
#endif
