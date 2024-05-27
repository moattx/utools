
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

/*
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

	str[strcspn(str, "\n")] = ' ';

out:
	if (fclose(fp) != 0)
		err(EXIT_FAILURE, " ");
}
*/

// Read text from a file and trim newline
void
readfile (const char *path, char *rstr, size_t size)
{
  assert (size > 1);
  FILE *fp;
  char *str = malloc (size);
  assert (str != NULL);

  if ((fp = fopen (path, "r")) == NULL)
    goto out;

  // read char bytes in fp until size and store it in str
  (void) fread (str, sizeof (char), size, fp);

  // remove trailing newline
  str[strcspn (str, "\n")] = 0;

  memcpy (rstr, str, size);

out:
  free (str);
  if (fclose (fp) != 0)
    err (EXIT_FAILURE, " ");
}
