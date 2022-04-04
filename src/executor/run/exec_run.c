/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:52:54 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 06:12:11 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "executor.h"
#include "heredoc.h"
#include "lexer.h"
#include "minishell.h"
#include "sighandler.h"
#include "status.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static int	_exec_fork(t_exec *exec, int *pids)
{
	pids[exec->index] = fork();
	if (pids[exec->index] == -1)
	{
		free(pids);
		perror(PROGRAM_NAME);
		return (0);
	}
	if (pids[exec->index] == 0)
	{
		free(pids);
		exec_fork(exec);
	}
	++exec->meta->started;
	if (exec->index != 0 && (exec - 1)->fds[0] != STDIN_FILENO)
		close((exec - 1)->fds[0]);
	if (exec->index == exec->meta->count - 1 && exec->fds[0] != STDIN_FILENO)
		close(exec->fds[0]);
	if (exec->fds[1] != STDOUT_FILENO)
		close(exec->fds[1]);
	return (1);
}

int	exec_run(t_exec_meta *meta)
{
	size_t	n;
	pid_t	*pids;

	pids = exec_pids_init(meta);
	if (pids == NULL)
		return (0);
	sigint_ignore();
	n = 0;
	while (n < meta->count)
	{
		if (exec_pipe(&meta->exec[n]) < 0)
		{
			free(pids);
			return (0);
		}
		if (n == 0 && meta->exec->is_builtin)
			exec_run_builtin(meta->exec);
		else
			_exec_fork(&meta->exec[n], pids);
		++n;
	}
	exec_wait(meta, pids);
	exec_run_cleanup(meta, pids);
	return (1);
}
