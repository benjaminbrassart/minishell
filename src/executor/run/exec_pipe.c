/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:10:54 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 00:51:20 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	exec_pipe(t_exec *exec)
{
	int	res;

	if (exec->index == exec->meta->count - 1)
	{
		exec->fds[0] = STDIN_FILENO;
		exec->fds[1] = STDOUT_FILENO;
		return (0);
	}
	res = pipe(exec->fds);
	if (res < 0)
		perror(PROGRAM_NAME);
	return (res);
}
