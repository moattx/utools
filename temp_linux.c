
/*
 * utools - power_netbsd.c
 * (C) 2023 moatx
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include "temp.h"
#include "util.h"

#define BUFF_SIZE 6
#define FILE_NAME "/sys/class/thermal/thermal_zone0/temp"

uintmax_t
temp(void)
{
	char temp[BUFF_SIZE];

	readfile(FILE_NAME, temp, sizeof(temp));
	return (strtoull(temp, NULL, 10) / 1000);
}
