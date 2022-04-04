/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 06:02:33 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 06:12:58 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "heredoc.h"
#include "minishell.h"
#include "status.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	_replace_input(t_exec *exec)
{
	if (exec->fd_in != STDIN_FILENO)
	{
		if (dup2(exec->fd_in, STDIN_FILENO) == -1)
		{
			perror(PROGRAM_NAME);
			lex_close_last_heredoc(exec);
			exit(EXIT_STATUS_MAJOR);
		}
		close(exec->fd_in);
	}
}

static void	_replace_output(t_exec *exec)
{
	if (exec->fd_out != STDOUT_FILENO)
	{
		if (dup2(exec->fd_out, STDOUT_FILENO) == -1)
		{
			perror(PROGRAM_NAME);
			lex_close_last_heredoc(exec);
			exit(EXIT_STATUS_MAJOR);
		}
		close(exec->fd_out);
	}
}

void	exec_fork(t_exec *exec)
{
	if (exec->index == exec->meta->count - 1 && exec->fds[1] != STDOUT_FILENO)
	{
		close(exec->fds[1]);
		exec->fd_out = STDOUT_FILENO;
	}
	exec_run_setup_child(exec);
	if (exec->fds[0] != STDIN_FILENO && exec->fds[0] != exec->fd_in)
		close(exec->fds[0]);
	_replace_input(exec);
	_replace_output(exec);
	lex_close_last_heredoc(exec);
	if (exec->index != 0 && (exec - 1)->fds[0] != STDIN_FILENO)
		close((exec - 1)->fds[0]);
	if ((exec->index == exec->meta->count - 1) && exec->fds[0] != STDIN_FILENO)
		close(exec->fds[0]);
	exec_run_child(exec);
}
