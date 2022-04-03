/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_concat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 03:27:52 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/03 04:13:55 by bbrassar         ###   ########.fr       */
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

static int	_destroy(t_buffer *buf)
{
	buffer_delete(buf);
	perror(PROGRAM_NAME);
	return (0);
}

static int	_not_word(int *isarg, t_buffer *buf, t_token_node *node,
	t_token_list *new_list)
{
	if ((*isarg && (!buffer_flush(buf) || !list_add(new_list, WORD, buf->buf)))
		|| (node != NULL && node->token != SEPARATOR
			&& !list_add(new_list, node->token, NULL)))
		return (_destroy(buf));
	buffer_init(buf);
	*isarg = 0;
	return (1);
}

int	lex_concat(t_token_list *list)
{
	t_buffer		buf;
	t_token_list	new_list;
	t_token_node	*node;
	int				is_arg;

	ft_memset(&new_list, 0, sizeof (new_list));
	new_list.sh = list->sh;
	node = list->first_node;
	is_arg = 0;
	buffer_init(&buf);
	while (1)
	{
		if (node == NULL || (node->token & ~WORD))
		{
			if (!_not_word(&is_arg, &buf, node, &new_list))
				return (0);
			if (node == NULL)
				break ;
		}
		else if (node->token & WORD)
		{
			if (!buffer_append(&buf, node->value))
				return (_destroy(&buf));
			if (((node->token & (WORD_DQ | WORD_SQ))
					|| ((node->token & WORD_NQ) && *node->value != 0)))
				is_arg = 1;
		}
		node = node->next;
	}
	lex_delete(list);
	ft_memmove(list, &new_list, sizeof (*list));
	return (1);
}
