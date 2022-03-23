/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_heredoc_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 08:14:45 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/23 01:39:42 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "ft.h"
#include "heredoc.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static void	heredoc_read_eof(char const *delimiter)
{
	t_buffer	buffer;

	buffer_init(&buffer);
	if (buffer_append(&buffer, "\n" PROGRAM_NAME ": warning: here-document "
			"delimited by end-of-file (wanted `")
		&& buffer_append(&buffer, delimiter)
		&& buffer_append(&buffer, "')\n") && buffer_flush(&buffer))
		write(STDERR_FILENO, buffer.buf, buffer.length);
	buffer_delete(&buffer);
}

int	lex_heredoc_read(t_heredoc *heredoc)
{
	size_t	n;
	int		fd;
	char	*line;

	n = 0;
	while (n < heredoc->count)
	{
		fd = dup(STDIN_FILENO);
		if (fd == -1)
			return (0);
		while (1)
		{
			line = readline(HEREDOC_PROMPT);
			if (line && ft_strcmp(heredoc->buffers[n].delimiter, line) != 0)
			{
				if (!buffer_append(&heredoc->buffers[n].buffer, line)
					|| !buffer_cappend(&heredoc->buffers[n].buffer, '\n'))
					return (buffer_delete(&heredoc->buffers[n].buffer), free(line), 0);
			}
			else
			{
				if (line)
					close(STDIN_FILENO);
				else
					heredoc_read_eof(heredoc->buffers[n].delimiter);
				free(heredoc->buffers[n].delimiter);
				dup2(fd, STDIN_FILENO);
				close(fd);
				break ;
			}
			free(line);
		}
		if (!buffer_flush(&heredoc->buffers[n].buffer))
			return (buffer_delete(&heredoc->buffers[n].buffer), 0);
		++n;
	}
	return (1);
}
