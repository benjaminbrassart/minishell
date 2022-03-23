/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 05:43:38 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/22 16:10:36 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "heredoc.h"

static int	_heredoc(t_token_node *node, t_heredoc *heredoc, size_t n)
{
	t_buffer	buffer;

	buffer_init(&buffer);
	node = node->next;
	while (node && (node->token & WORD))
	{
		if (!buffer_append(&buffer, node->value))
		{
			buffer_delete(&buffer);
			return (0);
		}
		node = node->next;
	}
	if (!buffer_flush(&buffer))
	{
		buffer_delete(&buffer);
		return (0);
	}
	heredoc->buffers[n].delimiter = buffer.buf;
	return (1);
}

int	lex_heredoc(t_token_list *list, t_heredoc *heredoc)
{
	size_t			n;
	t_token_node	*node;

	if (!lex_heredoc_build(list, heredoc))
		return (0);
	n = 0;
	node = list->first_node;
	while (node && n < heredoc->count)
	{
		while (node && node->token != D_LESS)
			node = node->next;
		if (node && node->next && (node->next->token & WORD))
		{
			if (!_heredoc(node, heredoc, n))
				return (0);
		}
		else
			return (1);
		++n;
	}
	return (lex_heredoc_read(heredoc));
}
