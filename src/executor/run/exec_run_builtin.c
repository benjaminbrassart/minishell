/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 06:34:28 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/01 06:22:19 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <unistd.h>

static int	try_dup(int fd, int *fd_out)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
	{
		perror(PROGRAM_NAME);
		return (0);
	}
	*fd_out = new_fd;
	return (1);
}

static int	try_dup2(int fd, int fd2)
{
	if (dup2(fd, fd2) == -1)
	{
		perror(PROGRAM_NAME);
		return (0);
	}
	return (1);
}

void	exec_run_builtin(t_exec *exec)
{
	t_env_table *const	env = &exec->meta->sh->env;
	int					save_fd[2];

	// printf("<parent>, stdin: %d, stdout: %d\n", exec->fd_in, exec->fd_out);
	if (!exec_redirect(exec)
		|| !try_dup(STDIN_FILENO, &save_fd[0])
		|| !try_dup(STDOUT_FILENO, &save_fd[1])
		|| !try_dup2(exec->fd_in, STDIN_FILENO)
		|| !try_dup2(exec->fd_out, STDOUT_FILENO))
		return ;
	if (exec->fd_in != STDIN_FILENO && exec->fd_in != exec->fds[0])
		close(exec->fd_in);
	if (exec->fd_out != STDOUT_FILENO && exec->fd_out != exec->fds[1])
		close(exec->fd_out);
	exec->interface.builtin(exec->argc, exec->argv, env);
	if (exec->fds[1] != STDOUT_FILENO)
		close(exec->fds[1]);
	if (!try_dup2(save_fd[0], STDIN_FILENO)
		|| !try_dup2(save_fd[1], STDOUT_FILENO))
		return ;
	close(save_fd[0]);
	close(save_fd[1]);
}
