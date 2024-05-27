/*
 * simple timer utility - counts down set timer 
 */

/*
 * utools - timer.c
 * (C) 2024 moatx
 * Released under the GNU GPLv2+, see the COPYING file
 * in the source distribution for its full text.
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>

static void
usage (void)
{
  extern char *__progname;
  fprintf (stderr, "usage: %s [HH:MM:SS] [MM:SS]\n", __progname);
  fprintf (stderr, "usage: see %s(1)\n", __progname);
}

void countdown (int timer[], int countdown);

// XXX: if there is more than one flag set, then using the ':' seperator,
// seperates each number into their respecive array slot
int
main (int argc, char **argv)
{
  if (argc < 2 || argc > 2)
    {
      usage ();
      goto err;
    }

  if (':' == argv[1][0] || ':' == argv[1][strlen (argv[1])])
    {
      fprintf (stderr, "wrong colon location\n");
      goto err;
    }
  int numcolon = 0;
  for (int i = 0; argv[1][i] != '\0'; i++)
    {
      if (argv[1][i] == ':')
	{
	  if (!isdigit (argv[1][i - 1]) && !isdigit (argv[1][i + 1]))
	    {
	      fprintf (stderr, "wrong charector\n");
	      goto err;
	    }
	  numcolon += 1;
	}
    }

  if (numcolon > 2 || numcolon < 1)
    {
      fprintf (stderr, "wrong number of colons\n");
      goto err;
    }
  // minutes
  if (numcolon == 1)
    {
      int timer[2];
      timer[0] = atoi (&argv[1][0]);
      timer[1] = atoi (&argv[1][2]);
      countdown (timer, numcolon);
    }
  else
    {
      int timer[3];
      timer[0] = atoi (&argv[1][0]);
      timer[1] = atoi (&argv[1][2]);
      timer[2] = atoi (&argv[1][4]);
      countdown (timer, numcolon);
    }
  return EXIT_SUCCESS;
err:
  return EXIT_FAILURE;
}

void
countdown (int timer[], int numcolon)
{
  for (;;)
    {
      if (timer[numcolon] == 0)
	{

	  if (numcolon == 2)
	    {
	      if (timer[numcolon] == 0
		  && timer[numcolon - 1] == 0 && timer[numcolon - 2] == 0)
		{
		  break;
		}
	      if (timer[numcolon - 2] != 0)
		{
		  timer[numcolon - 1] = timer[numcolon - 2] * 60;
		  timer[numcolon - 2] = timer[numcolon - 2] - 1;
		}
	      if (timer[numcolon - 1] != 0)
		{
		  timer[numcolon - 1] = timer[numcolon - 1] - 1;
		}
	      timer[numcolon] = 60;
	    }
	  else
	    {
	      if (timer[numcolon] == 0 && timer[numcolon - 1] == 0)
		{
		  break;
		}
	      timer[numcolon] = 60;
	      timer[numcolon - 1] = timer[numcolon - 1] - 1;
	    }
	}
      if (numcolon == 1)
	{
	  printf ("timer: %i:%i\n", timer[0], timer[1]);
	}
      else
	{
	  printf ("timer: %i:%i:%i\n", timer[0], timer[1], timer[2]);
	}
      sleep (1);
      timer[numcolon] = timer[numcolon] - 1;
    }
}
