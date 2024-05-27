
/*
 * utools - temp.c
 * (C) 2024 moatx
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
*/

#include <stdio.h>
#include "temp.h"

char *USAGE = "";

int
main(void)
{
	printf("%ju%%\n", temp());
	return 0;
}
