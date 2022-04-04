/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 05:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 03:46:53 by bbrassar         ###   ########.fr       */
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

	if (exec->is_builtin)
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
	int			status;
	int			err;

	err = 0;
	if (stat(exec->interface.path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			err = EISDIR;
			status = EXIT_STATUS_NON_EXECUTABLE;
		}
		else if (access(exec->interface.path, X_OK) != 0)
			status = EXIT_STATUS_NON_EXECUTABLE;
		else
			return ;
	}
	else
		status = EXIT_STATUS_NOT_FOUND;
	if (err == 0)
		err = errno;
	ft_perror(exec->argv[0], strerror(err));
	child_destroy(exec);
	exit(status);
}

void	exec_run_child(t_exec *exec)
{
	char	**envp;

	if (exec->argc == 0)
	{
		child_destroy(exec);
		exit(0);
	}
	lex_close_last_heredoc(exec);
	_exec_builtin(exec);
	_exec_nf(exec);
	if (exec->argc > 0)
		_exec_path(exec);
	envp = env_toarray(&exec->meta->sh->env);
	if (!envp)
	{
		ft_perror(exec->argv[0], strerror(errno));
		exit(EXIT_STATUS_MAJOR);
	}
	execve(exec->interface.path, exec->argv, envp);
	ft_perror(exec->argv[0], strerror(errno));
	child_destroy(exec);
	exit(EXIT_STATUS_NON_EXECUTABLE);
}
