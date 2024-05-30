timer(1)

# NAME

timer - countdown until set timer reaches zero

# SYNOPSIS

*timer* [HH:MM:SS] [MM:SS]

# DESCRIPTION

The *timer* utility reads the first argument. If the first argument has numbers seperated by one colon, then the left-most number is the minutes, and the right-most number is the seconds. 

_Omitting_ a digit after the colon would place in a zero for you.

otherwise, if it is seperated by two colons, then the left-most is the hour, the center is the minutes, and the right-most is the seconds.

*timer* is hard-set to only allow 3 digits per colon(s), except for seconds.

*timer* would countdown until each number seperated by the colons reaches zero.

# AUTHORS
utools author - moatx (_spelled lowercase_)
