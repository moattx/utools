
/*
 * utools - power_netbsd.c
 * (C) 2023 moatx
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
*/


#ifndef POWER_H_
#define POWER_H_
#include <stdbool.h>
bool is_connected(void);
double get_percent(void);
#endif /* !POWER_H_ */
