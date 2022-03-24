/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_heredoc_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 08:14:45 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/24 05:30:07 by bbrassar         ###   ########.fr       */
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

static void	_delim(char const *line, char *delimiter, int fd)
{
	if (line)
		close(STDIN_FILENO);
	else
		heredoc_read_eof(delimiter);
	free(delimiter);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static int	_loop(t_heredoc_buffer *hdbuf, int fd)
{
	char	*line;
	int		res;

	res = 1;
	while (res)
	{
		line = readline(HEREDOC_PROMPT);
		if (line && ft_strcmp(hdbuf->delimiter, line) != 0)
		{
			if (!buffer_append(&hdbuf->buffer, line)
				|| !buffer_cappend(&hdbuf->buffer, '\n'))
			{
				buffer_delete(&hdbuf->buffer);
				res = 0;
			}
		}
		else
		{
			_delim(line, hdbuf->delimiter, fd);
			free(line);
			break ;
		}
		free(line);
	}
	return (res);
}

int	lex_heredoc_read(t_heredoc *heredoc)
{
	size_t	n;
	int		fd;

	n = 0;
	while (n < heredoc->count)
	{
		fd = dup(STDIN_FILENO);
		if (fd == -1 || !_loop(&heredoc->buffers[n], fd))
			return (0);
		if (!buffer_flush(&heredoc->buffers[n].buffer))
			return (buffer_delete(&heredoc->buffers[n].buffer), 0);
		++n;
	}
	return (1);
}
