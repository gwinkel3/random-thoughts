#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE   42

#define SUCCESS     1
#define FAILURE     0

static char buf[BUF_SIZE];

int error_msg (const char *format, ...)
{
  va_list args;
  int     res;

  va_start (args, format);
  res = vfprintf (stderr, format, args);
  va_end (args);
  return res;
}

int read_double (double *d)
  /**** Returns SUCCESS or FAILURE, if FAILURE, the value of '*d' is
        undefined. */
{
  size_t length;

  for (;;) {
    /**** Prompt */
    printf ("Please enter a floating point number: ");
    fflush (stdout);
    /**** Read into buffer */
    if (!fgets (buf, sizeof (buf), stdin)) return FAILURE;
    /**** Remove trailing newline, if any */
    length = strlen (buf);
    if (buf[length-1] == '\n') {
      buf[--length] = '\0';
      /**** Attempt the conversion. */

        char *end;

        errno = 0;
        /**** Convert the value, setting error indicators. */
        *d = strtod (buf, &end);
        /**** Break the look if no error. */
        if (!errno && length && !*end) break;
        /**** Print an error message. */
        if (errno != 0) {
          error_msg ("Illegal input: %s\n", strerror (errno));
          error_msg ("The error was detected at the position "
                     "indicated below:\n");
        } else {
          error_msg ("Illegal input: there's an error at the position "
                     "indicated below:\n");
        } /* end if - else */
        error_msg ("    %s\n", buf);
        error_msg ("    %*c\n", (int) (end - buf) + 1, '^');

    } else {
      /**** There was no newline in the buffer: swallow extra
            characters. */
      scanf ("%*[^\n]");
      /**** We have the newline as dessert... */
      (void) getchar ();
      /**** Tell the user not to try to trick us: */
      error_msg ("Input too long. Don't type more than %d characters!\n",
                 BUF_SIZE);

    } /* end if - else */
  } /* end for */
  return SUCCESS;
} /* end read_double */

int main(void)
{
    double sof;
    read_double(&sof);

return 0;
}
