/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:52:54 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/23 03:32:33 by bbrassar         ###   ########.fr       */
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
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

static void	_setup_child(t_exec *exec)
{
	sigint_default();
	sigquit_default();
	if (!exec_redirect(exec))
	{
		child_destroy(exec);
		exit(EXIT_STATUS_MAJOR);
	}
	if (dup2(exec->fd_in, STDIN_FILENO) == -1
		|| dup2(exec->fd_out, STDOUT_FILENO) == -1)
	{
		perror(PROGRAM_NAME);
		child_destroy(exec);
		exit(EXIT_STATUS_MAJOR);
	}
	lex_heredoc_write(exec);
}

static void	_exec_builtin(t_exec *exec)
{
	t_env_table *const	env = &exec->meta->sh->env;
	int					status;

	if (exec->is_builtin)
	{
		status = exec->interface.builtin(exec->argc, exec->argv, env);
		child_destroy(exec);
		exit(status);
	}
}

static void	_exec_nf(t_exec *exec)
{
	if (exec->interface.path == NULL)
	{
		if (exec->search_path)
			ft_perror(exec->argv[0], MESSAGE_COMMAND_NF);
		child_destroy(exec);
		exit(EXIT_STATUS_NOT_FOUND);
	}
}

static void	_exec_path(t_exec *exec)
{
	int			status;
	struct stat	st;

	status = 0;
	if (stat(exec->interface.path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_perror(exec->argv[0], MESSAGE_EXEC_DIR);
			status = EXIT_STATUS_NON_EXECUTABLE;
		}
		else if (access(exec->interface.path, X_OK) != 0)
		{
			ft_perror(exec->argv[0], strerror(errno));
			status = EXIT_STATUS_NON_EXECUTABLE;
		}
	}
	else
	{
		ft_perror(exec->argv[0], strerror(errno));
		status = EXIT_STATUS_NOT_FOUND;
	}
	if (status)
	{
		child_destroy(exec);
		exit(status);
	}
}

static void	exec_child(t_exec *exec)
{
	char	**envp;

	_setup_child(exec);
	_exec_builtin(exec);
	_exec_nf(exec);
	_exec_path(exec);
	envp = env_toarray(&exec->meta->sh->env);
	if (envp)
	{
		close_fds(exec->meta);
		execve(exec->interface.path, exec->argv, envp);
	}
	ft_perror(exec->argv[0], strerror(errno));
	child_destroy(exec);
	exit(EXIT_STATUS_MAJOR);
}

int	exec_run(t_exec_meta *meta)
{
	size_t	n;
	pid_t	*pids;
	int		status;
	int		save_fd[2];

	pids = malloc(sizeof (*pids) * meta->count);
	if (pids == NULL)
	{
		perror(PROGRAM_NAME);
		return (0);
	}
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
	exec_delete_redirect(meta);
	parent_close(meta, -1);
	free(pids);
	sigint_install();
	return (1);
}
