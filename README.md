utools - a collection of user tools
===================================

utools is a collection of user tools that aid in retrieving data from a system. 

utools currently only supports Linux.

The following are the tools that are included in utools: 

	power.c		prints the battery percentage and whether or not its charging
	mem.c		prints free, used, and total memory for the system
	temp.c  	prints the cpu's temperature

INSTALLING
----------

To install, simply do:

    meson --buildtype=release build
    ninja -C build
    sudo ninja -C build install

LICENSE
-------
GNU General Public License, version 2 (GPL-2.0) or, at your option, any later version.
