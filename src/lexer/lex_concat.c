/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_concat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 03:27:52 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/11 05:45:17 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "ft.h"
#include "lexer.h"
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

int	lex_concat(t_token_list *list)
{
	t_buffer		buffer;
	t_token_list	new_list;
	t_token_node	*node;

	ft_memset(&new_list, 0, sizeof (new_list));
	node = list->first_node;
	buffer_init(&buffer);
	while (node)
	{
		if ((node->token & WORD) && !buffer_append(&buffer, node->value))
			return (buffer_delete(&buffer), 0);
		if (!(node->token & WORD))
		{
			if ((buffer.length || buffer.position) && (!buffer_flush(&buffer)
					|| !list_add(&new_list, WORD, buffer.buf)))
				return (buffer_delete(&buffer), 0);
			if (node->token != SEPARATOR && !list_add(&new_list, node->token, NULL))
				return (0);
			buffer_init(&buffer);
		}
		node = node->next;
	}
	if (!buffer_flush(&buffer)
		|| (buffer.length && !list_add(&new_list, WORD, buffer.buf)))
		return (0);
	lex_delete(list);
	ft_memmove(list, &new_list, sizeof (*list));
	return (1);
}