/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_heredoc_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 07:14:17 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/28 11:41:45 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "heredoc.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static t_exec_red	*last_heredoc(t_exec *exec)
{
	t_exec_red	*red;
	t_exec_red	*last;

	red = exec->red;
	last = NULL;
	while (red)
	{
		if (red->type == D_LESS)
			last = red;
		else if (red->type == LESS)
			last = NULL;
		red = red->next;
	}
	return (last);
}

int	lex_heredoc_write(t_exec *exec)
{
	t_exec_red			*red;
	t_heredoc_buffer	*buf;

	red = last_heredoc(exec);
	if (red)
	{
		buf = &exec->meta->sh->heredoc.buffers[red->hd_idx];
		if (write(buf->fd, buf->buffer.buf, buf->buffer.length) < 0)
		{
			perror(PROGRAM_NAME);
			close(buf->fd);
			return (0);
		}
		close(buf->fd);
	}
	return (1);
}
