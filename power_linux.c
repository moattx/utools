/*
 * utools - power_netbsd.c
 * (C) 2023 moatx
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
*/


#include "power.h"
#include "util.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATUS_STRING "Discharging"

#ifndef NDEBUG
static bool is_int_or_empty(const char *str);
#endif

bool
is_connected(void)
{
	//13
	char status[13];

	readfile(status, "/sys/class/power_supply/BAT0/status",
	    sizeof(STATUS_STRING));

	//ASERT NOT EMPTY STRING

	debug_print("status = %s\n", status);
	/*
        debug_print("strncmp = %i\n", strncmp(status, STATUS_STRING,
            sizeof(STATUS_STRING)));
	*/

	if (strncmp(status, "Not charging", strlen("Not charging")) == 0)
		return true;

	if (strncmp(status, "Full", strlen("Full")) == 0)
		return true;

	return (strncmp(status, "Discharging", sizeof(status)) != -1) ?
	    false : true;
}

double
get_percent(void)
{
	char percent[4];

	readfile(percent, "/sys/class/power_supply/BAT0/capacity",
	    sizeof(percent));
	//readfile(percent, " ", sizeof(percent));

	debug_print("percent = %s\n", percent);

	assert(is_int_or_empty(percent) == true);

	return atof(percent);
}

#ifndef NDEBUG
static bool
is_int_or_empty(const char *str)
{
	/* 0 because 2 is null terminator */
	unsigned int i = 0;

	/* Handle negative numbers. */
	if (*str == '-')
		++str;

	/* Handle empty string or just "-" */
	if (!*str)
		return false;

	debug_print("str = %s\n", str);
	debug_print("strlen = %li \n", strlen(str));

	/* (strlen - 1) to get rid of \0 */
	for (; i < (strlen(str) - 1); ++i) {
		debug_print("str[i] = %c\n", str[i]);
		if (isdigit(str[i])) {
			continue;
		} else {
			return false;
		}
	}
	/*
        while(i != strlen(str)){
          if(!isdigit(str[i++])){
            continue;
          }else{
            return false;
          }
        }
      */

	return true;
}
#endif
