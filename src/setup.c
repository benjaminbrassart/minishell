/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 09:24:19 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/14 18:05:33 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include "minishell.h"
#include "sighandler.h"
#include <signal.h>
#include <unistd.h>

static void	setup_signal_handlers(void)
{
	sigint_install();
	sigquit_ignore();
}

int	setup(t_sh *sh, char *ev[])
{
	const t_sh	sh_init = {
		.tokens = {.sh = sh, .first_node = NULL, .last_node = NULL, 0},
		.env = {.first_entry = NULL, .last_entry = NULL, .count = 0, .sh = sh},
		.heredoc = {.buffers = NULL, .count = 0},
		.force_exit = 0,
	};

	ft_memmove(sh, &sh_init, sizeof (sh_init));
	setup_signal_handlers();
	return (env_init(&sh->env, ev));
}
