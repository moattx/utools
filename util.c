
/*
 * utools - power_netbsd.c
 * (C) 2023 moatx
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>
#include <err.h>
#include <string.h>
#include <assert.h>
#include "util.h"

/* human readable puts */
void
rputs(double size)
{
	int i = 0;
	const char *units[] = {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
	while (size > 1024) {
		size /= 1024;
		i++;
	}
	printf("%.*f %s\n", i, size, units[i]);
}

void
readfile(char *str, char *dir, size_t strl)
{
	FILE *fp;
	//assert(str == NULL);
	assert(str);
	assert(dir);
	//assert(dir != NULL);
	//assert(dir[0] != '\0');
	//assert(strcmp(dir, " "));


	if ((fp = fopen(dir, "r")) == NULL)
		goto out;

	(void)fread(str, sizeof(str), strl, fp);
	if (ferror(fp))
		goto out;

	/* remove trailing newline */
	str[strcspn(str, "\n")] = ' ';

out:
	if (fclose(fp) != 0)
		err(EXIT_FAILURE, " ");
}
