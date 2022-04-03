/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 09:24:19 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/03 05:13:26 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include "minishell.h"
#include "sighandler.h"
#include "utils.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	setup_signal_handlers(void)
{
	sigint_install();
	sigquit_ignore();
}

static int	set_shlvl(t_env_table *env)
{
	char	*shlvl_var;
	char	*end;
	int		shlvl;
	int		res;

	shlvl_var = env_get(env, "SHLVL");
	shlvl = 0;
	if (shlvl_var)
	{
		shlvl = ft_strtoi(shlvl_var, &end);
		if (shlvl_var == end || *end != 0)
			shlvl = 0;
	}
	res = 0;
	shlvl_var = ft_itoa(++shlvl);
	if (shlvl_var)
	{
		res = env_set(env, "SHLVL", shlvl_var);
		free(shlvl_var);
	}
	if (!res)
		perror(PROGRAM_NAME);
	return (res);
}

int	_set_interactive(t_sh *sh)
{
	sh->is_interactive &= isatty(STDIN_FILENO);
	if (!sh->is_interactive)
	{
		if (errno == EBADF)
			ft_perror("failed to set interactive mode", strerror(errno));
		else
			return (1);
		return (0);
	}
	sh->is_interactive &= isatty(STDERR_FILENO);
	if (!sh->is_interactive)
	{
		if (errno == EBADF)
			ft_perror("failed to set interactive mode", strerror(errno));
		else
			return (1);
		return (0);
	}
	return (1);
}

int	setup(t_sh *sh, char *ev[])
{
	const t_sh	sh_init = {
		.tokens = {.sh = sh, .first_node = NULL, .last_node = NULL, 0},
		.env = {.first_entry = NULL, .last_entry = NULL, .count = 0, .sh = sh},
		.heredoc = {.sh = sh, .buffers = NULL, .count = 0},
		.force_exit = 0,
		.is_interactive = 1,
	};

	ft_memmove(sh, &sh_init, sizeof (sh_init));
	setup_signal_handlers();
	return (_set_interactive(sh) && env_init(&sh->env, ev)
		&& set_shlvl(&sh->env));
}
