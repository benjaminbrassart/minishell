/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:52:54 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/02 14:26:03 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "executor.h"
#include "lexer.h"
#include "minishell.h"
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
			if (!meta->exec[n].is_builtin)
				free(meta->exec[n].interface.path);
		}
		++n;
	}
	if (index < 0)
		free(meta->exec);
}

static void	child_destroy(t_exec *exec)
{
	env_destroy(&exec->meta->sh->env);
	lex_delete(&exec->meta->sh->tokens);
	parent_close(exec->meta, (int)(exec - exec->meta->exec));
}

static void	exec_child(t_exec *exec)
{
	t_env_table *const	env = &exec->meta->sh->env;
	char				**envp;
	int					status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (exec->is_builtin)
	{
		status = exec->interface.builtin(exec->argc, exec->argv, env);
		child_destroy(exec);
		exit(status);
	}
	else if (exec->interface.path == NULL)
	{
		if (exec->search_path)
			builtin_error(exec->argv[0], "Command not found");
		exit(EXIT_STATUS_NOT_FOUND);
	}
	envp = env_toarray(&exec->meta->sh->env);
	if (envp && dup2(exec->fd_in, STDIN_FILENO) != -1
		&& dup2(exec->fd_out, STDOUT_FILENO) != -1)
		execve(exec->interface.path, exec->argv, envp);
	perror(PROGRAM_NAME);
	child_destroy(exec);
	exit(EXIT_STATUS_MAJOR);
}

int	exec_run(t_exec_meta *meta)
{
	size_t	n;
	pid_t	*pids;
	int		offset;
	int		status;

	offset = 0;
	if (meta->exec[0].is_builtin)
		++offset;
	pids = malloc(sizeof (*pids) * meta->count);
	if (!pids)
		return (0);
	n = 0;
	while (n < meta->count)
	{
		if (n == 0 && offset)
			g_exit_status = meta->exec[n].interface.builtin(meta->exec[n].argc,
					meta->exec[n].argv, &meta->exec[n].meta->sh->env);
		else
		{
			pids[n] = fork();
			if (pids[n] == -1)
				return (perror(PROGRAM_NAME), 0);
			if (pids[n] == 0)
				exec_child(&meta->exec[n]);
		}
		++n;
	}
	parent_close(meta, -1);
	n = 0;
	if (offset)
		++n;
	while (n < meta->count)
	{
		if (waitpid(pids[n], &status, 0) == -1)
			return (perror(PROGRAM_NAME), 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				meta->sh->prompt = NULL;
			g_exit_status = WTERMSIG(status) + 128;
		}
		else if (WIFSTOPPED(status))
			g_exit_status = WSTOPSIG(status) + 128;
		++n;
	}
	free(pids);
	return (1);
}
