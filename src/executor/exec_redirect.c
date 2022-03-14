/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:42:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/11 07:12:38 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executor.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

// TODO handle heredoc
static int	open_red(t_exec_red *red)
{
	int	fds[2];

	red->fd = -1;
	if (red->type == D_LESS)
	{
		if (pipe(fds) >= 0)
		{
			red->fd = fds[0];
			red->exec->meta->sh->heredoc.buffers[red->hd_idx].fd = fds[1];
		}
	}
	else if (red->type == LESS)
		red->fd = open(red->path, O_RDONLY);
	else if (red->type == GREAT)
		red->fd = open(red->path, O_WRONLY | O_CREAT | O_TRUNC,
				REDIRECTION_UMASK);
	else if (red->type == D_GREAT)
		red->fd = open(red->path, O_WRONLY | O_CREAT | O_APPEND,
				REDIRECTION_UMASK);
	if (red->fd != -1)
		return (1);
	builtin_error(red->path, strerror(errno));
	return (0);
}

int	exec_redirect(t_exec *exec)
{
	t_exec_red	*red;
	t_exec_red	*last_heredoc;

	red = exec->red;
	last_heredoc = NULL;
	while (red)
	{
		if (!open_red(red))
			return (0);
		if (red->type & RED_IN)
		{
			if (red->type & D_LESS)
			{
				if (last_heredoc)
					close(last_heredoc->fd);
				last_heredoc = red;
			}
			if (exec->fd_in != STDIN_FILENO)
				close(exec->fd_in);
			exec->fd_in = red->fd;
		}
		else if (red->type & RED_OUT)
		{
			if (exec->fd_out != STDOUT_FILENO)
				close(exec->fd_out);
			exec->fd_out = red->fd;
		}
		red = red->next;
	}
	return (1);
}
