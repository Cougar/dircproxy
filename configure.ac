dnl Process this file with autoconf to produce a configure script.
AC_INIT(src/dircproxy.h)
AM_INIT_AUTOMAKE(dircproxy, 1.0.4)
AM_CONFIG_HEADER(config.h)
AC_CANONICAL_HOST
AM_MAINTAINER_MODE

dnl Checks for programs.
AC_PROG_AWK
AC_PROG_CC
AC_ISC_POSIX
AM_PROG_CC_STDC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_RANLIB
AC_PROG_MAKE_SET

dnl Checks for libraries.

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(crypt.h fcntl.h inttypes.h sys/time.h syslog.h unistd.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_TYPE_UID_T

dnl Checks for library functions.
AC_FUNC_ALLOCA
AC_TYPE_SIGNAL
AC_FUNC_STRFTIME
AC_CHECK_FUNCS(mkdir rmdir seteuid strcspn strerror strspn strstr strtoul)
AC_CHECK_FUNC(socket,  , 
	      AC_CHECK_LIB(socket, socket, , AC_MSG_WARN([couldn't find your socket() function]))
	      )
AC_CHECK_FUNC(gethostbyname, , 
	      AC_CHECK_LIB(nsl, gethostbyname, , AC_MSG_WARN([couldn't find your gethostbyname() function]))
	      )
AC_CHECK_FUNC(crypt, , 
	      AC_CHECK_LIB(crypt, crypt, , AC_MSG_WARN([couldn't find your crypt() function]))
	      )

dnl Do strange debug stuff.
AC_ARG_ENABLE(debug, [  --enable-debug          turn on debugging [default=no]],
	      [if eval "test x$enable_debug = xyes"; then
		      CFLAGS="-g -Wall $CFLAGS"
		      AC_DEFINE([DEBUG], 1, [Do we debug stuff?])
		      AC_DEFINE([DEBUG_MEMORY], 1, [Turn on expensive (but cool) memory debugging])
	      else
		      AC_CHECK_FUNCS(strdup vasprintf vsnprintf)
	      fi],
	      [AC_CHECK_FUNCS(strdup vasprintf vsnprintf)]
)

dnl Allow me to turn on/off poll and select to debug stuff
AC_ARG_ENABLE(poll, [  --disable-poll          disable use of the poll() function [default=no]],
	      [if eval "test x$enable_poll = xyes"; then
		      AC_CHECK_FUNCS(poll)
		      AC_CHECK_HEADERS(poll.h sys/poll.h)
	      fi],
	      [AC_CHECK_FUNCS(poll)
	      AC_CHECK_HEADERS(poll.h sys/poll.h)]
)

AC_ARG_ENABLE(select,
	      [  --disable-select        disable use of the select() function [default=no]],
	      [if eval "test x$enable_select = xyes"; then
		      AC_CHECK_FUNCS(select)
	      fi],
	      [AC_CHECK_FUNCS(select)]
)

dnl Output the Makefiles.
AC_OUTPUT([Makefile
           conf/Makefile
	   contrib/Makefile
	   getopt/Makefile
	   crypt/Makefile
	   doc/Makefile
	   src/Makefile])