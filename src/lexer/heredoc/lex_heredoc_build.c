/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_heredoc_build.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 05:59:27 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/02 22:55:54 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "ft.h"
#include "heredoc.h"
#include "lexer.h"
#include "token.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	lex_heredoc_build(t_token_list *list, t_heredoc *heredoc)
{
	t_token_node	*node;
	size_t			n;

	node = list->first_node;
	while (node)
	{
		if (node->token == D_LESS)
			++heredoc->count;
		node = node->next;
	}
	heredoc->buffers = ft_calloc(heredoc->count, sizeof (*heredoc->buffers));
	if (!heredoc->buffers)
	{
		perror(PROGRAM_NAME);
		return (0);
	}
	n = 0;
	while (n < heredoc->count)
	{
		buffer_init(&heredoc->buffers[n].buffer);
		heredoc->buffers[n].heredoc = heredoc;
		heredoc->buffers[n].delimiter = NULL;
		++n;
	}
	return (1);
}
