/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:42:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/22 05:18:56 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executor.h"
#include "utils.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static void	_red_in(t_exec_red *red, t_exec_red **last_heredoc)
{
	if (red->type & D_LESS)
	{
		if (last_heredoc)
			close((*last_heredoc)->fd);
		*last_heredoc = red;
	}
	if (red->exec->fd_in != STDIN_FILENO)
		close(red->exec->fd_in);
	red->exec->fd_in = red->fd;
}

static void	_red_out(t_exec_red *red)
{
	if (red->exec->fd_out != STDOUT_FILENO)
		close(red->exec->fd_out);
	red->exec->fd_out = red->fd;
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
			break ;
		if (red->type & RED_IN)
			_red_in(red, &last_heredoc);
		else if (red->type & RED_OUT)
			_red_out(red);
		red = red->next;
	}
	exec_delete_redirect(exec->meta);
	return (red == NULL);
}
