/*
 * utools - power_netbsd.c
 * (C) 2023 moatx
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
*/

#include <unistd.h>
#include <getopt.h>
#include "mem.h"
#include "util.h"

char *USAGE = "[-utf]";

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

	while ((ch = getopt(argc, argv, "utf")) != -1) {
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
		default:
			usage(EXIT_FAILURE);
		}
	}
	return 0;
}
