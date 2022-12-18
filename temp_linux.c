/* See LICENSE file for copyright and license details. */
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

	readfile(temp, FILE_NAME, sizeof(temp));
	return (strtoull(temp, NULL, 10) / 1000);
}
