/* dircproxy
 * Copyright (C) 2000 Scott James Remnant <scott@netsplit.com>.
 * All Rights Reserved.
 *
 * help.h
 * --
 * @(#) $Id: help.h,v 1.5 2000/10/16 10:42:39 keybuk Exp $
 *
 * This file is distributed according to the GNU General Public
 * License.  For full details, read the top of 'main.c' or the
 * file called COPYING that was distributed with this code.
 */

#ifndef __DIRCPROXY_HELP_H
#define __DIRCPROXY_HELP_H

/* help index */
static char *help_index[] = {
  "dircproxy can be controlled using the /DIRCPROXY command.",
  "This command takes one or more parameters, the first of",
  "which is a command, the rest of which depend on the",
  "command chosen.",
  "",
  "Valid commands:",
  0
};
static char *help_index_end[] = {
  "",
  "For more information on a command, use /DIRCPROXY HELP",
  "followed by the command",
  0
};

/* help help */
static char *help_help[] = {
  "/DIRCPROXY HELP",
  "displays general help on dircproxy and a list of valid",
  "commands.",
  "",
  "/DIRCPROXY HELP [command]",
  "displays specific help on the requested command.",
  0
};

/* help quit */
static char *help_quit[] = {
  "/DIRCPROXY QUIT [quit message]",
  "detaches you from dircproxy, and also ends the proxied",
  "session to the server.  This is the only way to do this.",
  "An optional /QUIT message may be supplied, you may need",
  "to prefix this with a : if it contains spaces.",
  0
};

/* help detach */
static char *help_detach[] = {
  "/DIRCPROXY DETACH [away message]",
  "detaches you from dircproxy, and sets an optional away",
  "message.  This usually has the same effect as simply",
  "closing your client, or using your clients /QUIT command.",
  "The away message may need to be prefixed with a : if it",
  "contains spaces",
  0
};

/* help recall */
static char *help_recall[] = {
  "/DIRCPROXY RECALL [from] <lines>",
  "/DIRCPROXY RECALL ALL",
  "recalls log messages from the server/private message log",
  "file.  You can specify the number of lines to recall, and",
  "a starting point in the file, or you can specify ALL to",
  "recall all log messages",
  "",
  "/DIRCPROXY RECALL <nickname> [from] lines>",
  "/DIRCPROXY RECALL <nickname> ALL",
  "recalls log messages from the server/private message log",
  "that were sent by the nickname given.  You can specify",
  "the number of lines to recall and an optional starting",
  "point (in the full log file).  You may also specify ALL.",
  "",
  "/DIRCPROXY RECALL <channel> [from] <lines>",
  "/DIRCPROXY RECALL <channel> ALL",
  "recalls log messages from the channel log specified.  You",
  "can specify the number of lines to recall and an optional",
  "starting point in the file, or you can specify ALL to",
  "recall all log messages",
  0
};

/* help persist */
static char *help_persist[] = {
  "/DIRCPROXY PERSIST",
  "for use if running dircproxy under inetd or if you have",
  "disconnect_on_detach set to yes in the config file.",
  "Tells dircproxy you want it to persist with its server",
  "connect and allow you to reattach later.  It will tell",
  "you which hostname and port you should use to reconnect",
  "(may not be the same as the one you originally connected",
  "to)",
  "",
  "This command has no effect for normal proxy sessions",
  0
};

/* help motd */
static char *help_motd[] = {
  "/DIRCPROXY MOTD",
  "displays the dircproxy message of the day that it gives",
  "you when you attach",
  0
};

/* help die */
static char *help_die[] = {
  "/DIRCPROXY DIE",
  "kills the dircproxy process on the server.  You won't",
  "be able to reconnect after you do this.",
  0
};

/* help servers */
static char *help_servers[] = {
  "/DIRCPROXY SERVERS",
  "displays a list of servers that dircproxy will cycle upon",
  "disconnection.  Current server is marked with an arrow",
  0
};

/* help jump (with new) */
static char *help_jump_new[] = {
  "/DIRCPROXY JUMP <num>",
  "disconnect from the current server and jump to the server",
  "in the /DIRCPROXY SERVERS list specified by number",
  "",
  "/DIRCPROXY JUMP <hostname>[:[port][:[password]]]",
  "disconnect from the current server and jump to the server",
  "specified",
  0
};

/* help jump (without new) */
static char *help_jump[] = {
  "/DIRCPROXY JUMP <num>",
  "disconnect from the current server and jump to the server",
  "in the /DIRCPROXY SERVERS list specified by number",
  "",
  "/DIRCPROXY JUMP <hostname>[:[port][:[password]]]",
  "disconnect from the current server and jump to the server",
  "in the /DIRCPROXY SERVERS list specified by the full",
  "details",
  0
};

/* help host */
static char *help_host[] = {
  "/DIRCPROXY HOST <hostname>",
  "disconnect from the current server, and reconnect to it",
  "again with a different locally available hostname.  This",
  "basically changes the local_address config option on the",
  "fly",
  "",
  "/DIRCPROXY HOST NONE",
  "disconnect from the current server, and reconnect to it",
  "again with the best available hostname.",
  "",
  "/DIRCPROXY HOST",
  "disconnect from the current server, and reconnect to it",
  "again with the hostname originally specified in the",
  "local_address config option (if any)",
  0
};

#endif /* __DIRCPROXY_HELP_H */
