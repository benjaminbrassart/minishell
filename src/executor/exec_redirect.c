/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:42:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/10 07:18:54 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executor.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

// TODO
static int	open_red(char const *path, int type)
{
	if (type == D_LESS)
		return (0);
	if (type == LESS)
		return (open(path, O_RDONLY));
	if (type == GREAT)
		return (open(path, O_WRONLY | O_CREAT | O_TRUNC,
				REDIRECTION_UMASK));
	if (type == D_GREAT)
		return (open(path, O_WRONLY | O_APPEND | O_CREAT,
				REDIRECTION_UMASK));
	return (-1);
}

int	exec_redirect(t_exec *exec)
{
	t_exec_red	*red;
	int			fd;

	red = exec->red;
	while (red)
	{
		fd = open_red(red->path, red->type);
		if (fd == -1)
		{
			builtin_error(red->path, strerror(errno));
			return (0);
		}
		if (red->type & LESS)
		{
			if (exec->fd_in != STDIN_FILENO)
				close(exec->fd_in);
			exec->fd_in = fd;
		}
		if (red->type & RED_OUT)
		{
			if (exec->fd_out != STDOUT_FILENO)
				close(exec->fd_out);
			exec->fd_out = fd;
		}
		red = red->next;
	}
	return (1);
}
