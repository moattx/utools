/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include "temp.h"

char *USAGE = "";

int
main(void)
{
	printf("%ju%%\n", temp());
	return 0;
}
