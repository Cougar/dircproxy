# DIP_NET
# Borrowed from xiph.org xiph_net.m4
# Perform tests required by the net module
AC_DEFUN([DIP_NET],
[dnl
AC_CHECK_HEADERS([sys/select.h sys/uio.h])

# These tests are ordered based on solaris 8 tests
AC_SEARCH_LIBS([sethostent], [nsl],
  [AC_DEFINE([HAVE_SETHOSTENT], [1],
    [Define if you have the sethostent function])])
AC_SEARCH_LIBS([getnameinfo], [socket],
  [AC_DEFINE([HAVE_GETNAMEINFO], [1],
    [Define if you have the getnameinfo function])])
AC_CHECK_FUNCS([endhostent getaddrinfo inet_aton writev])

# Irix defines INET_PTON but not sockaddr_storage!
AC_CHECK_MEMBERS([struct sockaddr_storage.ss_family],
  [AC_CHECK_FUNCS([inet_pton])],,
  [#include <sys/types.h> 
#include <sys/socket.h>])
])
