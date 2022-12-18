/* See LICENSE file for copyright and license details. */
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
