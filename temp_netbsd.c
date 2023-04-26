
/*
 * utools - power_netbsd.c
 * (C) 2023 moatx
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
*/


#include <stdio.h>
#include "temp.h"
#include "netbsd.h"

uintmax_t
temp(void)
{
	uintmax_t temp = get_value("temperature");
	temp = (temp / 1000000.0) - 273.15;
	return temp;
}


