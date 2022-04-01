/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:20:20 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/01 09:23:21 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executor.h"
#include "status.h"
#include "utils.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int	open_red(t_exec_red *red)
{
	int	fds[2];

	red->fd = -1;
	if (red->type == D_LESS)
	{
		if (pipe(fds) >= 0)
		{
			red->fd = fds[0];
			red->hd->fd = fds[1];
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
	ft_perror(red->path, strerror(errno));
	g_exit_status = EXIT_STATUS_MINOR;
	return (0);
}
