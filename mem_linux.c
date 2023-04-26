/*
 * utools - power_netbsd.c
 * (C) 2023 moatx
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
*/

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <err.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <sys/sysinfo.h>

/* get free memory */
double
getfree(void)
{
	struct sysinfo meminfo;
	sysinfo(&meminfo);
	return (double)meminfo.freeram;
}

/* get total physical memory */
double
getphy(void)
{
	struct sysinfo meminfo;
	sysinfo(&meminfo);
	return (double)meminfo.totalram;
}
