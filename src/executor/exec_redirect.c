/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:42:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/14 19:22:15 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executor.h"
#include "utils.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

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
