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
#include <limits.h>

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
  exit (EXIT_FAILURE);
}

static bool
handle_errors (const char *str, int numcolon)
{
  if (str[0] == ':')
    {
      fprintf (stderr, "wrong colon location\n");
      return true;
    }

  if (numcolon > 2 || numcolon < 1)
    {
      fprintf (stderr, "wrong number of colons\n");
      return true;
    }
  int numdigits = 0;
  for (int i = 0; str[i] != '\0'; i++)
    {
      numdigits++;
      if (str[i] == ':')
	{
	  if (numdigits > 3)
	    {
	      fprintf (stderr,
		       "error: more than three digits, besides seconds section\n");
	      return true;
	    }
	  numdigits = 0;
	}
      if (str[i + 1] == '\0')
	{
	  if (numdigits > 2)
	    {
	      fprintf (stderr,
		       "error: more than two digits in second section\n");
	      return true;
	    }
	}
    }
  return false;
}

static int
str2int (const char *str)
{
  int rint = 0;

  for (int x = 0; str[x] != '\0'; x++)
    {
      rint = rint * 10 + str[x] - '0';
    }
  return rint;
}

static void
split_substring (const char *string, char *retstring, char div, int *pos)
{
  // XXX: minus one because deliminar 
  // char *retstring = malloc(strlen(string) * sizeof(char));
  // char *retstring[strlen(string)];
  int i = *pos != 0 ? *pos + 1 : *pos;
  // for retstring
  int x = 0;

  for (; string[i] != div; i++)
    {
      retstring[x] = string[i];
      x++;
    }
  // add a null terminator to mark as string
  // retstring[x + 1] = '\0';
  retstring[x] = '\0';
  *pos = i;
  // return retstring;

}

void countdown (int timer[], int numcolon);

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

  int numcolon = 0;
  // get the number of colons
  for (int i = 0; argv[1][i] != '\0'; i++)
    {
      if (argv[1][i] == ':')
	{
	  numcolon += 1;
	}
    }

  if (handle_errors (argv[1], numcolon))
    goto err;

  int pos = 0;
  // char *str;
  size_t size = strlen (argv[1]);
  char *retstring = malloc (size * sizeof (char));

  // minutes MM:SS
  if (numcolon == 1)
    {
      int timer[2];

      split_substring (argv[1], retstring, ':', &pos);
      timer[0] = str2int (retstring);

      split_substring (argv[1], retstring, '\0', &pos);
      timer[1] = str2int (retstring);

      // timer[0] = str2int(split_substring(argv[1], ':', &pos));
      // timer[1] = str2int(split_substring(argv[1], '\0', &pos));
      countdown (timer, numcolon);
      // free(&timer[0]);
    } // hours HH:MM:SS
  else
    {
      int timer[3];
      // char *str;
      split_substring (argv[1], retstring, ':', &pos);
      timer[0] = str2int (retstring);

      split_substring (argv[1], retstring, ':', &pos);
      timer[1] = str2int (retstring);

      split_substring (argv[1], retstring, '\0', &pos);
      timer[2] = str2int (retstring);
      // timer[0] = str2int(split_substring(argv[1], ':', &pos));
      // timer[1] = str2int(split_substring(argv[1], ':', &pos));
      // timer[2] = str2int(split_substring(argv[1], '\0', &pos));
      countdown (timer, numcolon);
    }
  // get cursor back
  free (retstring);
  printf ("\33[?25h");
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
	  printf ("\rtimer: %i:%i\r", timer[0], timer[1]);
	}
      else
	{
	  printf ("\rtimer: %i:%i:%i", timer[0], timer[1], timer[2]);
	}
      fflush (stdout);
      // clear stdout
      printf("\33[2K\r");
      sleep (1);
      timer[numcolon] = timer[numcolon] - 1;
    }
}
