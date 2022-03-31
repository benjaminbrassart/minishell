/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:52:54 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/31 06:22:36 by bbrassar         ###   ########.fr       */
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
		perror(PROGRAM_NAME);
		return (0);
	}
	if (pids[exec->index] == 0)
	{
		close(exec->fds[0]);
		if (exec->index != 0)
			dup2(exec->meta->exec[exec->index - 1].fds[0], STDIN_FILENO); // ! handle
		close(exec->meta->exec[exec->index - 1].fds[0]);
		if (exec->index != exec->meta->count - 1)
			dup2(exec->fds[1], STDOUT_FILENO); // ! handle
		close(exec->fds[1]);
		free(pids);
		exec_run_child(exec);
	}
	if (exec->index == exec->meta->count - 1)
		close(exec->fds[0]);
	if (exec->index != 0)
		close(exec->meta->exec[exec->index - 1].fds[0]);
	close(exec->fds[1]);
	return (1);
}

static void	_wait_child(t_exec_meta *meta, pid_t *pids, size_t n)
{
	int	status;

	if (waitpid(pids[n], &status, 0) == -1)
	{
		perror(PROGRAM_NAME);
		return ;
	}
	g_exit_status = get_exit_status(status);
	if (n == meta->count - 1 && WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			handle_sigint(0);
		if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, MESSAGE_CHILD_QUIT "\n",
				sizeof (MESSAGE_CHILD_QUIT));
		if (WTERMSIG(status) == SIGSEGV)
			write(STDERR_FILENO, MESSAGE_CHILD_SEGV "\n",
				sizeof (MESSAGE_CHILD_SEGV));
	}
}

static void	_cleanup(t_exec_meta *meta, pid_t *pids)
{
	size_t	n;

	n = 0;
	if (meta->exec->is_builtin || meta->exec->argc == 0)
		++n;
	close_fds(meta);
	while (n < meta->count)
		_wait_child(meta, pids, n++);
	exec_delete_redirect(meta);
	parent_close(meta, -1);
	free(pids);
	sigint_install();
}

int	exec_run(t_exec_meta *meta)
{
	size_t	n;
	pid_t	*pids;

	pids = malloc(sizeof (*pids) * meta->count);
	if (pids == NULL)
	{
		perror(PROGRAM_NAME);
		return (0);
	}
	sigint_ignore();
	if (pids == NULL)
		return (0);
	n = 0;
	while (n < meta->count)
	{
		if (pipe(meta->exec[n].fds) == -1)
			return (0); // ! handle error properly
		if (n == 0 && (meta->exec->is_builtin || meta->exec[n].argc == 0))
			exec_run_builtin(meta->exec);
		else
			_exec_fork(&meta->exec[n], pids);
		++n;
	}
	_cleanup(meta, pids);
	return (1);
}
