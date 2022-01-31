/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 00:06:36 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 08:34:00 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "type/sh.h"
# include <signal.h>

# define COMMAND_PROMPT "\033[32m$ \033[0m"
# define PROGRAM_NAME "minishell"
# define MAX_INT_DIGITS 11

static volatile sig_atomic_t	g_exit_status;

void	handle_signal(int sig);

int		setup(t_sh *sh, char *ev[]);

#endif
