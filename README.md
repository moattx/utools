utools - a collection of user tools
===================================

utools is a collection of user tools that aid in retrieving data from a system or aid in its intented function(s).

utools currently only supports Linux, plans for other os(es) only occur when I need to use them on it.

The following are the tools that are included in utools: 

	power.c		prints the battery percentage and whether or not its charging
	mem.c		prints free, used, and total memory for the system
	temp.c  	prints the cpu's temperature
	timer.c     	prints the timer, until it reaches zero. see timer(1).

INSTALLING
----------

To install, simply do:

    meson build
    ninja -C build
    sudo ninja -C build install

LICENSE
-------
GNU General Public License, version 2 (GPL-2.0) or, at your option, any later version.
