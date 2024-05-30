/*
 * utools - mem.c
 * (C) 2023 moatx
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
*/

#include <unistd.h>
#include <getopt.h>
#include "mem.h"
#include "util.h"

char *USAGE = "[-utfh]";

int
main(int argc, char **argv)
{
	int ch;
#ifdef __NetBSD__
	//puts("BSD");
	setprogname(argv[0]);
#endif
	if (argc == 1)
		usage(EXIT_SUCCESS);

	while ((ch = getopt(argc, argv, "utfh")) != -1) {
		switch (ch) {
		case 'u':
			rputs((getphy() - getfree()));
			break;
		case 't':
			rputs(getphy());
			break;
		case 'f':
			rputs(getfree());
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		case '?':
		default:
			usage(EXIT_FAILURE);
		}
	}
	return 0;
}
