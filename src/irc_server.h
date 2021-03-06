/* dircproxy
 * Copyright (C) 2000-2003 Scott James Remnant <scott at netsplit dot com>
 * 
 * Copyright (C) 2004-2008 Francois Harvey <contact at francoisharvey dot ca>
 * 
 * Copyright (C) 2008-2009 Noel Shrum <noel dot w8tvi at gmail dot com>
 *                         Francois Harvey <contact at francoisharvey dot ca>
 * 
 * 
 * irc_server.h
 * --
 * @(#) $Id: irc_server.h,v 1.8 2002/12/29 21:30:12 scott Exp $
 *
 * This file is distributed according to the GNU General Public
 * License.  For full details, read the top of 'main.c' or the
 * file called COPYING that was distributed with this code.
 */

#ifndef __DIRCPROXY_IRC_SERVER_H
#define __DIRCPROXY_IRC_SERVER_H

/* required includes */
#include "irc_net.h"

/* functions */
extern int ircserver_connect(struct ircproxy *);
extern int ircserver_close_sock(struct ircproxy *);
extern int ircserver_connectagain(struct ircproxy *);
extern void ircserver_resetidle(struct ircproxy *);
extern int ircserver_send_command(struct ircproxy *, const char *, const char *,
                                  ...);

#endif /* __DIRCPROXY_IRC_SERVER_H */
