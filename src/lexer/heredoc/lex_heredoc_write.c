/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_heredoc_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 07:14:17 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/02 22:02:27 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "builtin.h"
#include "heredoc.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	lex_heredoc_write(t_exec *exec)
{
	t_exec_red			*red;
	t_heredoc_buffer	*buf;
	int					res;

	red = lex_get_last_heredoc(exec, 0);
	res = 1;
	if (red)
	{
		buf = red->hd;
		if (write(buf->fd, buf->buffer.buf, buf->buffer.length) < 0)
		{
			perror(PROGRAM_NAME);
			res = 0;
		}
		buffer_delete(&buf->buffer);
		close(buf->fd);
	}
	return (res);
}
