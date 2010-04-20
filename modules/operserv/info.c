/*
 * Copyright (c) 2010 Atheme Development Group, et al.
 * Rights to this code are as documented in doc/LICENSE.
 *
 * This file contains code for OS INFO
 *
 * $Id: info.c 7895 2010-04-17 02:40:03Z jdhore $
 */

#include "atheme.h"

DECLARE_MODULE_V1
(
	"operserv/info", false, _modinit, _moddeinit,
	"$Id: info.c 7895 2010-04-17 02:40:03Z jdhore $",
	"Atheme Development Group <http://www.atheme.org>"
);

static void os_cmd_info(sourceinfo_t *si, int parc, char *parv[]);

command_t os_info = { "INFO", N_("Shows some useful information about the current settings of services."), PRIV_SERVER_AUSPEX, 1, os_cmd_info };

list_t *os_cmdtree;
list_t *os_helptree;

void _modinit(module_t *m)
{
	MODULE_USE_SYMBOL(os_cmdtree, "operserv/main", "os_cmdtree");
	MODULE_USE_SYMBOL(os_helptree, "operserv/main", "os_helptree");

        command_add(&os_info, os_cmdtree);
	help_addentry(os_helptree, "INFO", "help/oservice/info", NULL);
}

void _moddeinit()
{
	command_delete(&os_info, os_cmdtree);
	help_delentry(os_helptree, "INFO");
}

static void os_cmd_info(sourceinfo_t *si, int parc, char *parv[])
{
	logcommand(si, CMDLOG_GET, "INFO");

	command_success_nodata(si, "How often services writes changes to the database: %d minutes", config_options.commit_interval / 60);
	command_success_nodata(si, "Default kline time: %d days", config_options.kline_time / 86400);
	command_success_nodata(si, "Will services be sending WALLOPS/GLOBOPS about various things: %s", config_options.silent ? "no" : "yes");
	command_success_nodata(si, "How many messages before a flood is triggered, (if 0, flood protection is disabled): %d", config_options.flood_msgs);
	command_success_nodata(si, "How long before the flood counter resets: %d seconds", config_options.flood_time);
	command_success_nodata(si, "No nick ownership enabled: %s", nicksvs.no_nick_ownership ? "yes" : "no");
        command_success_nodata(si, "Nickname expiration time: %d days", nicksvs.expiry / 86400);
	command_success_nodata(si, "Nickname enforce expiry time: %d days", nicksvs.enforce_expiry / 86400);
	command_success_nodata(si, "Nickname enforce delay: %d seconds", nicksvs.enforce_delay);
	command_success_nodata(si, "Nickname enforce prefix: %s", nicksvs.enforce_prefix);
	command_success_nodata(si, "Maximum number of logins allowed per username: %d", me.maxlogins);
	command_success_nodata(si, "Maximum number of usernames that can be registered to one email address: %d", me.maxusers);
	if (!nicksvs.no_nick_ownership)
		command_success_nodata(si, "Maximum number of nicknames that one user can own: %d", me.maxnicks);
	command_success_nodata(si, "Maximum number of channels that one user can own: %d", me.maxchans);
        command_success_nodata(si, "Channel expiration time: %d days", chansvs.expiry / 86400);
	if (chansvs.fantasy)
		command_success_nodata(si, "Channel fantasy trigger: %s", chansvs.trigger);
	command_success_nodata(si, "Maximum number of entries allowed in a channel access list (if 0, unlimited): %d", chansvs.maxchanacs);
	command_success_nodata(si, "Maximum number of founders allowed per channel: %d", chansvs.maxfounders);

}

/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs
 * vim:ts=8
 * vim:sw=8
 * vim:noexpandtab
 */