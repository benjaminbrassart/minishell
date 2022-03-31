/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 05:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/31 20:41:25 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "executor.h"
#include "heredoc.h"
#include "status.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static void	_exec_builtin(t_exec *exec)
{
	t_env_table *const	env = &exec->meta->sh->env;
	int					status;

	if (exec->is_builtin || exec->argc == 0)
	{
		status = g_exit_status;
		if (exec->is_builtin)
			status = exec->interface.builtin(exec->argc, exec->argv, env);
		child_destroy(exec);
		exit(status);
	}
}

static void	_exec_nf(t_exec *exec)
{
	if (exec->interface.path == NULL && exec->argc > 0)
	{
		if (exec->search_path)
			ft_perror(exec->argv[0], MESSAGE_COMMAND_NF);
		child_destroy(exec);
		exit(EXIT_STATUS_NOT_FOUND);
	}
}

static void	_exec_path(t_exec *exec)
{
	struct stat	st;

	if (stat(exec->interface.path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_perror(exec->argv[0], MESSAGE_EXEC_DIR);
			exit(EXIT_STATUS_NON_EXECUTABLE);
		}
		if (access(exec->interface.path, X_OK) != 0)
		{
			ft_perror(exec->argv[0], strerror(errno));
			exit(EXIT_STATUS_NON_EXECUTABLE);
		}
	}
	else
	{
		ft_perror(exec->argv[0], strerror(errno));
		exit(EXIT_STATUS_NOT_FOUND);
	}
}

void	exec_run_child(t_exec *exec)
{
	char	**envp;

	exec_run_setup_child(exec);
	fprintf(stderr, "pid: %d, stdin: %d, stdout: %d\n", getpid(),
		exec->fds[0], exec->fds[1]);
	_exec_builtin(exec);
	_exec_nf(exec);
	_exec_path(exec);
	envp = env_toarray(&exec->meta->sh->env);
	if (envp)
	{
		// lex_heredoc_close(exec);
		execve(exec->interface.path, exec->argv, envp);
	}
	ft_perror(exec->argv[0], strerror(errno));
	// child_destroy(exec);
	exit(EXIT_STATUS_MAJOR);
}
