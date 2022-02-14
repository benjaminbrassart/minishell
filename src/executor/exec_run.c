/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:52:54 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/14 11:27:34 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "executor.h"
#include "lexer.h"
#include "minishell.h"
#include "status.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	exec_child(t_exec *exec)
{
	char	**envp;

	printf("FORKED PROCESS\n");
	lex_delete(&exec->meta->sh->tokens);
	if (exec->is_builtin)
		exit(exec->interface.builtin(exec->argc, exec->argv,
				&exec->meta->sh->env));
	else
	{
		env_destroy(&exec->meta->sh->env);
		envp = env_toarray(&exec->meta->sh->env);
		env_destroy(&exec->meta->sh->env);
		if (envp && dup2(STDIN_FILENO, exec->fd_in) != -1
			&& dup2(STDOUT_FILENO, exec->fd_out) != -1)
			execve(exec->interface.path, exec->argv, envp);
	}
	perror(PROGRAM_NAME);
	exit(EXIT_STATUS_MAJOR);
}

static void	parent_close(t_exec_meta *meta)
{
	(void)meta;
}

int	exec_run(t_exec_meta *meta)
{
	size_t	n;
	pid_t	*pids;
	int		offset;

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
		{
			printf("PARENT PROCESS\n");
			meta->exec[n].interface.builtin(meta->exec[n].argc,
				meta->exec[n].argv, &meta->exec[n].meta->sh->env);
		}
		else
		{
			pids[n] = fork();
			if (pids[n] == -1)
				return (0);
			if (pids[n] == 0)
				exec_child(&meta->exec[n]);
		}
		++n;
	}
	parent_close(meta);
	n = 0;
	while (n < meta->count)
	{
		if (!offset)
			wait(NULL);
		++n;
	}
	return (1);
}
