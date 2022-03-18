/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_heredoc_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 07:14:17 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/11 08:16:31 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "heredoc.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static t_exec_red	*last_heredoc(t_exec *exec)
{
	t_exec_red	*iter;
	t_exec_red	*red;

	iter = exec->red;
	red = NULL;
	while (iter)
	{
		if (iter->hd_idx >= 0)
			red = iter;
		iter = iter->next;
	}
	return (red);
}

int	lex_heredoc_write(t_exec_meta *meta)
{
	t_exec_red			*red;
	t_heredoc_buffer	*buf;
	size_t				n;

	n = 0;
	while (n < meta->count)
	{
		red = last_heredoc(&meta->exec[n]);
		if (red)
		{
			buf = &meta->sh->heredoc.buffers[red->hd_idx];
			if (write(buf->fd, buf->buffer.buf, buf->buffer.length) < 0)
			{
				close(buf->fd);
				perror(PROGRAM_NAME);
				return (0);
			}
			close(buf->fd);
		}
		++n;
	}
	return (1);
}