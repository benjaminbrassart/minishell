/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:52:54 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/24 06:30:48 by bbrassar         ###   ########.fr       */
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

static void	_exec_builtin(t_exec *exec)
{
	t_env_table *const	env = &exec->meta->sh->env;
	int					save_fd[2];

	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	dup2(exec->fd_in, STDIN_FILENO);
	dup2(exec->fd_out, STDOUT_FILENO);
	if (exec->fd_in != STDIN_FILENO)
		close(exec->fd_in);
	if (exec->fd_out != STDOUT_FILENO)
		close(exec->fd_out);
	g_exit_status = exec->interface.builtin(exec->argc, exec->argv, env);
	dup2(save_fd[0], STDIN_FILENO);
	dup2(save_fd[1], STDOUT_FILENO);
	close(save_fd[0]);
	close(save_fd[1]);
}

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
		free(pids);
		exec_run_child(exec);
	}
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
	if (meta->exec->is_builtin)
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
		if (n == 0 && meta->exec->is_builtin)
			_exec_builtin(meta->exec);
		else
			_exec_fork(&meta->exec[n], pids);
		++n;
	}
	_cleanup(meta, pids);
	return (1);
}
