/* dircproxy
 * Copyright (C) 2000 Scott James Remnant <scott@netsplit.com>.
 * All Rights Reserved.
 *
 * sprintf.c
 *  - various ways of doing allocating sprintf() functions to void b/o
 * --
 * @(#) $Id: sprintf.c,v 1.7 2000/08/25 09:38:23 keybuk Exp $
 *
 * This file is distributed according to the GNU General Public
 * License.  For full details, read the top of 'main.c' or the
 * file called COPYING that was distributed with this code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include <dircproxy.h>
#include "stringex.h"
#include "sprintf.h"

/* The sprintf() version is just a wrapper around whatever vsprintf() we
   decide to implement. */
char *x_sprintf(const char *format, ...) {
  va_list ap;
  char *ret;

  va_start(ap, format);
  ret = x_vsprintf(format, ap);
  va_end(ap);

  return ret;  
}

#ifdef HAVE_VASPRINTF

/* Wrap around vasprintf() which exists in BSD */
char *x_vsprintf(const char *format, va_list ap) {
  char *str;

  str = 0;
  vasprintf(&str, format, ap);

  return str;
}

#else /* HAVE_VASPRINTF */

# ifdef HAVE_VSNPRINTF

/* Does vsnprintf()s until its not truncated and returns the string */
char *x_vsprintf(const char *format, va_list ap) {
  int buffsz, ret;
  char *buff;

  buff = 0;
  buffsz = 0;

  do {
    buffsz += 64;
    buff = (char *)realloc(buff, buffsz + 1);

    ret = vsnprintf(buff, buffsz, format, ap);
  } while ((ret == -1) || (ret >= buffsz));

  return buff;
}

# else /* HAVE_VSNPRINTF */

/* These routines are based on those found in the Linux Kernel.  I've
 * rewritten them quite a bit (read completely) since then.
 *
 * Copyright (C) 1991, 1992  Linus Torvalds
 */

/* Makes a string representation of a number which can have different
   lengths, bases and precisions etc. */
static char *_x_makenum(long num, int base, int minsize, int mindigits,
                        char padchar, char signchar) {
  static char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
  unsigned long newstrlen;
  char *newstr;
  int i, j;

  if ((base < 2) || (base > 36) || (minsize < 0) || (mindigits < 0)) {
    return NULL;
  }

  newstr = x_strdup("");
  newstrlen = 1;

  if (signchar) {
    if (num < 0) {
      signchar = '-';
      num = -num;
    }
  }
  if (signchar == ' ') {
    signchar = 0;
  }

  if (!num) {
    newstr = (char *)realloc(newstr, newstrlen + 1);
    strcpy(newstr + newstrlen - 1, "0");
    newstrlen++;
  } else {
    while (num) {
      newstr = (char *)realloc(newstr, newstrlen + 1);
      newstr[newstrlen - 1] = digits[((unsigned long) num) % base];
      newstr[newstrlen] = 0;
      newstrlen++;
      num = ((unsigned long) num) / base;
    }
  }

  if (strlen(newstr) < mindigits) {
    mindigits -= strlen(newstr);
    while (mindigits--) {
      newstr = (char *)realloc(newstr, newstrlen + 1);
      strcpy(newstr + newstrlen - 1, "0");
      newstrlen++;
    }
  }

  if (signchar && (padchar != '0')) {
    newstr = (char *)realloc(newstr, newstrlen + 1);
    newstr[newstrlen - 1] = signchar;
    newstr[newstrlen] = 0;
    newstrlen++;
    signchar = 0;
  }

  if ((strlen(newstr) < minsize) && padchar) {
    minsize -= strlen(newstr);
    while (minsize--) {
      newstr = (char *)realloc(newstr, newstrlen + 1);
      newstr[newstrlen - 1] = padchar;
      newstr[newstrlen] = 0;
      newstrlen++;
    }
    if (signchar) {
      newstr[strlen(newstr)-1] = signchar;
      signchar = 0;
    }
  }

  if (signchar) {
    newstr = (char *)realloc(newstr, newstrlen + 1);
    newstr[newstrlen - 1] = signchar;
    newstr[newstrlen] = 0;
    newstrlen++;
  }

  i = strlen(newstr)-1;
  j = 0;
  while (i > j) {
    char tmpchar;

    tmpchar = newstr[i];
    newstr[i] = newstr[j];
    newstr[j] = tmpchar;
    i--;
    j++;
  }

  if ((strlen(newstr) < minsize) && !padchar) {
    char *tmpstr;

    i = minsize - strlen(newstr);
    tmpstr = (char *)malloc(i + 1);
    tmpstr[i--] = 0;
    while (i >= 0) {
      tmpstr[i--] = ' ';
    }

    tmpstr = (char *)realloc(tmpstr, strlen(tmpstr) + strlen(newstr) + 1);
    strcpy(tmpstr + strlen(tmpstr), newstr);
    free(newstr);
    newstr = tmpstr;
  }

  return newstr;
}

/* Basically vasprintf, except it doesn't do floating point or pointers */
char *x_vsprintf(const char *format, va_list ap) {
  char *newdest, *formatcpy, *formatpos, padding, signchar, qualifier;
  int width, prec, base, special, len, caps;
  unsigned long newdestlen;
  long num;

  newdest = x_strdup("");
  newdestlen = 1;
  formatpos = formatcpy = x_strdup(format);

  while (*formatpos) {
    if (*formatpos == '%') {
      padding = signchar = ' ';
      qualifier = 0;
      width = prec = special = caps = 0;
      base = 10;
      formatpos++;

      while (1) {
        if (*formatpos == '-') {
          padding = 0;
        } else if (*formatpos == '+') {
          signchar = '+';
        } else if (*formatpos == ' ') {
          signchar = (signchar == '+') ? '+' : ' ';
        } else if (*formatpos == '#') {
          special = 1;
        } else {
          break;
        }
        formatpos++;
      }

      if (*formatpos == '*') {
        width = va_arg(ap, int);
        if (width < 0) {
          width =- width;
          padding = 0;
        }
        formatpos++;
      } else {
        if (*formatpos == '0') {
          padding = '0';
          formatpos++;
        }

        while (isdigit(*formatpos)) {
          width *= 10;
          width += (*formatpos - '0');
          formatpos++;
        }
      }

      if (*formatpos == '.') {
        formatpos++;
        if (*formatpos == '*') {
          prec = abs(va_arg(ap, int));
          formatpos++;
        } else {
          while (isdigit(*formatpos)) {
            prec *= 10;
            prec += (*formatpos - '0');
            formatpos++;
          }
        }
      }

      if ((*formatpos == 'h') || (*formatpos == 'l')) {
        qualifier = *formatpos;
        formatpos++;
      }

      if (*formatpos == 'c') {
        if (padding) {
          while (--width > 0) {
            newdest = (char *)realloc(newdest, newdestlen + 1);
            newdest[newdestlen - 1] = padding;
            newdest[newdestlen] = 0;
            newdestlen++;
          }
        }

        newdest = (char *)realloc(newdest, newdestlen + 1);
        newdest[newdestlen - 1] = va_arg(ap, unsigned char);
        newdest[newdestlen] = 0;
        newdestlen++;

        if (!padding) {
          while (--width > 0) {
            newdest = (char *)realloc(newdest, newdestlen + 1);
            newdest[newdestlen - 1] = padding;
            newdest[newdestlen] = 0;
            newdestlen++;
          }
        }
      } else if (*formatpos == 's') {
        char *tmpstr;

        tmpstr = x_strdup(va_arg(ap, char *));
        len = (prec && (prec < strlen(tmpstr))) ? prec : strlen(tmpstr);
        if (padding) {
          while (--width > len) {
            newdest = (char *)realloc(newdest, newdestlen + 1);
            newdest[newdestlen - 1] = padding;
            newdest[newdestlen] = 0;
            newdestlen++;
          }
        }

        newdest = (char *)realloc(newdest, newdestlen + len);
        strncpy(newdest + newdestlen - 1, tmpstr, len);
        newdestlen += len;
        newdest[newdestlen - 1] = 0;
        free(tmpstr);

        if (!padding) {
          while (--width > len) {
            newdest = (char *)realloc(newdest, newdestlen + 1);
            newdest[newdestlen - 1] = padding;
            newdest[newdestlen] = 0;
            newdestlen++;
          }
        }
      } else if (strchr("oXxdiu", *formatpos) != NULL) {
        char *tmpstr;

        if (*formatpos == 'o') {
          base = 8;
          if (signchar) {
            signchar = 0;
          }
          if (special) {
            newdest = (char *)realloc(newdest, newdestlen + 1);
            strcpy(newdest + newdestlen - 1, "0");
            newdestlen++;
          }
        } else if (*formatpos == 'X') {
          base = 16;
          caps = 1;
          if (signchar) {
            signchar = 0;
          }
          if (special) {
            newdest = (char *)realloc(newdest, newdestlen + 1);
            strcpy(newdest + newdestlen - 1, "0");
            newdestlen++;
          }
        } else if (*formatpos == 'x') {
          base = 16;
          if (signchar) {
            signchar = 0;
          }
          if (special) {
            newdest = (char *)realloc(newdest, newdestlen + 2);
            strcpy(newdest + newdestlen - 1, "0x");
            newdestlen += 2;
          }
        } else if (*formatpos == 'i') {
          if (!signchar) {
            signchar = ' ';
          }
        } else if (*formatpos == 'u') {
          if (signchar) {
            signchar = 0;
          }
        }
        
        if (qualifier == 'l') {
          num = va_arg(ap, unsigned long);
        } else if (qualifier == 'h') {
          if (signchar) {
            num = va_arg(ap, signed short int);
          } else {
            num = va_arg(ap, unsigned short int);
          }
        } else if (signchar) {
          num = va_arg(ap, signed int);
        } else {
          num = va_arg(ap, unsigned int);
        }

        tmpstr = _x_makenum(num, base, width, prec, padding, signchar);
        if (caps)
          strupr(tmpstr);

        newdest = (char *)realloc(newdest, newdestlen + strlen(tmpstr));
        strcpy(newdest + newdestlen - 1, tmpstr);
        newdestlen += strlen(tmpstr);
        free(tmpstr);
      } else if (*formatpos == '%') {
        newdest = (char *)realloc(newdest, newdestlen + 1);
        newdest[newdestlen - 1] = *formatpos;
        newdest[newdestlen] = 0;
        newdestlen++;
      }
    } else {
      newdest = (char *)realloc(newdest, newdestlen + 1);
      newdest[newdestlen - 1] = *formatpos;
      newdest[newdestlen] = 0;
      newdestlen++;
    }

    formatpos++;
  }

  free(formatcpy);
  return newdest;
}

# endif /* HAVE_VSNPRINTF */
#endif /* HAVE_VASPRINTF */

#ifdef HAVE_STRDUP

/* Wrap around strdup() */
char *x_strdup(const char *s) {
  return strdup(s);
}

#else /* HAVE_STRDUP */

/* Do the malloc and strcpy() ourselves so we don't annoy memdebug.c */
char *x_strdup(const char *s) {
  char *ret;

  ret = (char *)malloc(strlen(s) + 1);
  strcpy(ret, s);

  return ret;
}

#endif /* HAVE_STRDUP */
