/*
 * utools - power_netbsd.c
 * (C) 2023 moatx
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
*/

/*
 * htop - netbsd/Platform.c
 * (C) 2014 Hisham H. Muhammad
 * (C) 2015 Michael McConville
 * (C) 2021 Santhosh Raju
 * (C) 2021 Nia Alarie
 * (C) 2021 htop dev team
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
*/

/*
 * A tiny fraction of code was copied from htop's netbsd/Platform.c,
 * and was modified to do what I wanted it to do
 */

/* helper functions for netbsd that makes life easier */

#include <prop/proplib.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <paths.h>
#include <sys/envsys.h>
#include <fcntl.h>
#include "netbsd.h"

intmax_t
get_value(const char* cstring)
{
	prop_dictionary_t dict, fields;
	prop_object_t device, curvalue, descfield;
	prop_object_iterator_t diter, fiter;

	intmax_t value = 0;

	int fd = open(_PATH_SYSMON, O_RDONLY);
	if (fd == -1)
		goto error;

	if (prop_dictionary_recv_ioctl(fd, ENVSYS_GETDICTIONARY, &dict) != 0)
		goto error;

	diter = prop_dictionary_iterator(dict);
	if (diter == NULL)
		goto error;

	while ((device = prop_object_iterator_next(diter)) != NULL) {
		if ((fiter = prop_array_iterator(prop_dictionary_get_keysym(dict,
		    device))) == NULL)
			goto error;

		while ((fields = prop_object_iterator_next(fiter)) != NULL) {
			curvalue = prop_dictionary_get(fields, "cur-value");
			descfield = prop_dictionary_get(fields, "description");

			if (descfield == NULL || curvalue == NULL)
				continue;

			if (prop_string_equals_string(descfield,
			    cstring)) {
				value = prop_number_signed_value(curvalue);
			}
		}
	}
	return value;

error:
	if (fd != -1)
		close(fd);
	exit(EXIT_FAILURE);
}
