/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 04:58:17 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 05:57:17 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "sighandler.h"
#include "status.h"
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

static int	_set_offset(t_exec_meta *meta, size_t *offset_ptr)
{
	*offset_ptr = 0;
	if (meta->count > 0 && meta->exec->is_builtin)
		*offset_ptr = 1;
	return (*offset_ptr);
}

static void	_set_exit_status(int status)
{
	g_exit_status = get_exit_status(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			handle_sigint(0);
		if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, MESSAGE_CHILD_QUIT "\n",
				sizeof (MESSAGE_CHILD_QUIT));
		if (WTERMSIG(status) == SIGSEGV)
			write(STDERR_FILENO, MESSAGE_CHILD_SEGV "\n",
				sizeof (MESSAGE_CHILD_SEGV));
	}
}

void	exec_wait(t_exec_meta *meta, pid_t *pids)
{
	size_t	n;
	size_t	offset;
	pid_t	pid;
	int		status;

	n = _set_offset(meta, &offset);
	while (n - offset < meta->started)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		if (pid == pids[meta->started + offset - 1])
			_set_exit_status(status);
		++n;
	}
	if (n - offset != meta->started)
		perror(PROGRAM_NAME);
}
