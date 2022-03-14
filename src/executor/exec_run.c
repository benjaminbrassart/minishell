/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:52:54 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/14 17:16:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "executor.h"
//#include "heredoc.h"
#include "lexer.h"
#include "minishell.h"
#include "sighandler.h"
#include "status.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static void	parent_close(t_exec_meta *meta, int index)
{
	size_t	n;

	n = 0;
	while (n < meta->count)
	{
		if (index < 0 || (size_t)index != n)
		{
			free(meta->exec[n].argv);
			if (meta->exec[n].search_path)
				free(meta->exec[n].interface.path);
		}
		++n;
	}
	if (index < 0)
		free(meta->exec);
}

static void	close_fds(t_exec_meta *meta)
{
	size_t	n;

	n = 0;
	while (n < meta->count)
	{
		if (meta->exec[n].fd_in != STDIN_FILENO)
			close(meta->exec[n].fd_in);
		if (meta->exec[n].fd_out != STDOUT_FILENO)
			close(meta->exec[n].fd_out);
		++n;
	}
}

static void	child_destroy(t_exec *exec)
{
	env_destroy(&exec->meta->sh->env);
	lex_delete(&exec->meta->sh->tokens);
	parent_close(exec->meta, (int)(exec - exec->meta->exec));
	//lex_heredoc_delete(&exec->meta->sh->heredoc);
	free(exec->argv);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	if (!exec->is_builtin)
		free(exec->interface.path);
	free(exec->meta->exec);
}

static void	exec_child(t_exec *exec)
{
	t_env_table *const	env = &exec->meta->sh->env;
	char				**envp;
	int					status;

	sigint_default();
	sigquit_default();
	if (exec->is_builtin)
	{
		status = exec->interface.builtin(exec->argc, exec->argv, env);
		child_destroy(exec);
		exit(status);
	}
	else if (exec->interface.path == NULL)
	{
		if (exec->search_path)
			builtin_error(exec->argv[0], MESSAGE_COMMAND_NF);
		child_destroy(exec);
		exit(EXIT_STATUS_NOT_FOUND);
	}
	envp = env_toarray(&exec->meta->sh->env);
	if (envp && dup2(exec->fd_in, STDIN_FILENO) != -1
		&& dup2(exec->fd_out, STDOUT_FILENO) != -1)
	{
		close_fds(exec->meta);
		execve(exec->interface.path, exec->argv, envp);
	}
	perror(PROGRAM_NAME);
	child_destroy(exec);
	exit(EXIT_STATUS_MAJOR);
}

//static t_exec_red	*get_last_heredoc(t_exec *exec)
//{
//	t_exec_red	*iter;
//	t_exec_red	*red;

//	iter = exec->red;
//	red = NULL;
//	while (iter)
//	{
//		if (iter->type == D_LESS)
//			red = iter;
//		iter = iter->next;
//	}
//	return (red);
//}

int	exec_run(t_exec_meta *meta)
{
	size_t	n;
	pid_t	*pids;
	int		status;
	int		save_fd[2];

	pids = malloc(sizeof (*pids) * meta->count);
	if (!pids)
		return (0);
	sigint_ignore();
	n = 0;
	while (n < meta->count)
	{
		if (n == 0 && meta->exec->is_builtin)
		{
			save_fd[0] = dup(STDIN_FILENO);
			save_fd[1] = dup(STDOUT_FILENO);
			dup2(meta->exec->fd_in, STDIN_FILENO);
			dup2(meta->exec->fd_out, STDOUT_FILENO);
			if (meta->exec->fd_in != STDIN_FILENO)
				close(meta->exec->fd_in);
			if (meta->exec->fd_out != STDOUT_FILENO)
				close(meta->exec->fd_out);
			g_exit_status = meta->exec[n].interface.builtin(meta->exec[n].argc,
					meta->exec[n].argv, &meta->exec[n].meta->sh->env);
			dup2(save_fd[0], STDIN_FILENO);
			dup2(save_fd[1], STDOUT_FILENO);
			close(save_fd[0]);
			close(save_fd[1]);
		}
		else
		{
			pids[n] = fork();
			if (pids[n] == -1)
				return (perror(PROGRAM_NAME), 0);
			if (pids[n] == 0)
			{
				free(pids);
				exec_child(&meta->exec[n]);
			}
		}
		++n;
	}
	n = 0;
	if (meta->exec->is_builtin)
		++n;
	close_fds(meta);
	while (n < meta->count)
	{
		if (waitpid(pids[n], &status, 0) == -1)
			return (perror(PROGRAM_NAME), 0);
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
		++n;
	}
	parent_close(meta, -1);
	free(pids);
	sigint_install();
	return (1);
}
