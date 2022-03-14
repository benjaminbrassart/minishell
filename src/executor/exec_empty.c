/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_empty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 02:36:24 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/14 20:54:45 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "executor.h"
#include "utils.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

int	exec_empty(t_exec_meta *meta)
{
	t_exec		exec;
	t_exec_red	*red;

	meta->exec = &exec;
	exec.red = NULL;
	exec.meta = meta;
	meta->count = 1;
	if (exec_build_redirect(meta))
	{
		red = exec.red;
		while (red)
		{
			if (!open_red(red))
			{
				builtin_error(red->path, strerror(errno));
				return (0);
			}
			close(red->fd);
			red = red->next;
		}
	}
	return (1);
}
