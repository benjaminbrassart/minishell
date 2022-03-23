/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:43:42 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/23 03:40:44 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "status.h"
#include <stdio.h>
#include <unistd.h>

int	exec_pipe(t_exec_meta *meta)
{
	int		fds[2];
	size_t	n;

	n = 0;
	while (n < meta->count - 1)
	{
		if (pipe(fds) == -1)
		{
			g_exit_status = EXIT_STATUS_MINOR;
			perror(PROGRAM_NAME);
			return (0);
		}
		meta->exec[n].fd_out = fds[1];
		meta->exec[n + 1].fd_in = fds[0];
		++n;
	}
	return (1);
}
