/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run_setup_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 05:34:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/01 15:33:32 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "executor.h"
#include "heredoc.h"
#include "minishell.h"
#include "sighandler.h"
#include "status.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void	exec_run_setup_child(t_exec *exec)
{
	sigint_default();
	sigquit_default();
	if (!exec_redirect(exec))
	{
		close(exec->fd_in);
		close(exec->fd_out);
		child_destroy(exec);
		exit(EXIT_STATUS_MINOR);
	}
	lex_heredoc_write(exec);
}
