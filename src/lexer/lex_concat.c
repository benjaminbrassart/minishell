/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_concat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 03:27:52 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/02 15:27:33 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	list_add(t_token_list *list, int token, char *value)
{
	t_token_node	*node;

	node = malloc(sizeof (*node));
	if (!node)
		return (0);
	node->next = NULL;
	node->token = token;
	node->value = value;
	__lex_add(list, node);
	return (1);
}

static int	lex_concat_inline(t_buffer *buffer, t_token_list *new_list,
t_token_node *node)
{
	static t_token_node	*last_node = NULL;

	if ((node->token & WORD) && !buffer_append(buffer, node->value))
		return (0);
	if (node->token == WORD_NQ && *(node->value) == 0)
	{
		last_node = node;
		return (1);
	}
	if (node->token & ~WORD)
	{
		if (((last_node->token & (WORD_DQ | WORD_NQ)) || buffer->length
				|| buffer->position) && (!buffer_flush(buffer)
				|| !list_add(new_list, WORD, buffer->buf)))
			return (0);
		if (node->token != SEPARATOR && !list_add(new_list, node->token, NULL))
			return (0);
		buffer_init(buffer);
	}
	last_node = node;
	return (1);
}

int	lex_concat(t_token_list *list)
{
	t_buffer		buf;
	t_token_list	new_list;
	t_token_node	*slow;
	t_token_node	*node;

	ft_memset(&new_list, 0, sizeof (new_list));
	new_list.sh = list->sh;
	node = list->first_node;
	slow = NULL;
	buffer_init(&buf);
	while (node)
	{
		if (!lex_concat_inline(&buf, &new_list, node))
			return (buffer_delete(&buf), perror(PROGRAM_NAME), 0);
		slow = node;
		node = node->next;
	}
	if (slow && ((slow->token & (WORD_SQ | WORD_DQ))
			|| ((slow->token & WORD_NQ) && (buf.length || buf.position)))
		&& (!buffer_flush(&buf) || !list_add(&new_list, WORD, buf.buf)))
		return (0);
	lex_delete(list);
	ft_memmove(list, &new_list, sizeof (*list));
	return (1);
}
