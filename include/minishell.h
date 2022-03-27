/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 00:06:36 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/27 04:05:42 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "type/t_sh.h"

/* The prompt to show when waiting for a command */
# define DEFAULT_PROMPT "\033[0m$> "
# define PROGRAM_NAME "minishell"
# define EXIT_MESSAGE "exit"

void	handle_signal(int sig);

int		setup(t_sh *sh, char *ev[]);

#endif
