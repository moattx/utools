/*
 * utools - power.c
 * (C) 2022 moatx
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <fcntl.h>
#include <paths.h>
#include <unistd.h>
#include <getopt.h>
/*
#include <prop/proplib.h>
#include <sys/envsys.h>
*/
#include <signal.h>
#include <sys/stat.h>
#include "power.h"
#include "util.h"

char *USAGE = "[-cph]";

int
main(int argc, char **argv)
{
	int ch;
#ifdef __NetBSD__
	setprogname(argv[0]);
#endif
	if (argc == 1) {
		printf("%.2f%%\n", get_percent());
	}
	while ((ch = getopt(argc, argv, "pch")) != -1) {
		switch (ch) {
		case 'p':
			printf("%.2f%%\n", get_percent());
			break;
		case 'c':
			printf("%s\n", (is_connected()) ? "yes" : "no");
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		case '?':
		default:
			usage(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}
