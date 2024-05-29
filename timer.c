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
#include<signal.h>

static void
usage (void)
{
  extern char *__progname;
  fprintf (stderr, "usage: %s [HH:MM:SS] [MM:SS]\n", __progname);
  fprintf (stderr, "usage: see %s(1)\n", __progname);
}

static void
on_signal ()
{
  printf ("\33[?25h");
  exit (1);
}

void countdown (int timer[], int countdown);

int
main (int argc, char **argv)
{
  if (argc < 2 || argc > 2)
    {
      usage ();
      goto err;
    }
  // disable cursor
  printf ("\33[?25l");
  (void) signal (SIGHUP, on_signal);
  (void) signal (SIGINT, on_signal);
  (void) signal (SIGTERM, on_signal);

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
  // minutes MM:SS
  if (numcolon == 1)
    {
      int timer[2];
      timer[0] = atoi (&argv[1][0]);
      timer[1] = atoi (&argv[1][2]);
      countdown (timer, numcolon);
    } // hours HH:MM:SS
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
  // get cursor back
  printf ("\33[?25h");
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
		  // get cursor back
		  printf ("\33[?25h");
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
		  // get cursor back
		  printf ("\33[?25h");
		  break;
		}
	      timer[numcolon] = 60;
	      timer[numcolon - 1] = timer[numcolon - 1] - 1;
	    }
	}
      if (numcolon == 1)
	{
	  printf ("\rtimer: %i:%i\r", timer[0], timer[1]);
	}
      else
	{
	  printf ("\rtimer: %i:%i:%i", timer[0], timer[1], timer[2]);
	}
      fflush (stdout);
      sleep (1);
      timer[numcolon] = timer[numcolon] - 1;
    }
}
