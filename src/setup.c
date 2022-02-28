/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 09:24:19 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/18 18:47:03 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include "minishell.h"
#include <signal.h>

static void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

int	setup(t_sh *sh, char *ev[])
{
	const t_sh	sh_init = {
		.tokens = {NULL, NULL, 0},
		.env = {NULL, NULL, 0},
		.heredoc = {NULL, 0},
		.prompt = DEFAULT_PROMPT
	};

	ft_memmove(sh, &sh_init, sizeof (sh_init));
	handle_signal((int)(long)sh);
	setup_signal_handlers();
	return (env_init(&sh->env, ev));
}
