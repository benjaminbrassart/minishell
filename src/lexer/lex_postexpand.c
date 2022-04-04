/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_postexpand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:07:28 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 06:14:37 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static t_token_node	*_fill_node(t_token_node *node, char *s)
{
	if (s == NULL)
		node->token = SEPARATOR;
	else
		node->token = WORD_NQ;
	node->value = s;
	node->next = NULL;
	return (node);
}

static int	_add_word_sep(t_token_list *list, char *value)
{
	t_token_node	*new_node;

	new_node = malloc(sizeof (*new_node));
	if (!new_node)
		return (0);
	__lex_add(list, _fill_node(new_node, value));
	new_node = malloc(sizeof (*new_node));
	if (!new_node)
		return (0);
	__lex_add(list, _fill_node(new_node, NULL));
	return (1);
}

static int	_list_add_nq(t_token_list *list, t_token_node *node)
{
	char	**array;
	char	**ptr;

	array = ft_split(node->value, IFS);
	free(node->value);
	free(node);
	if (array == NULL)
	{
		perror(PROGRAM_NAME);
		return (0);
	}
	ptr = array;
	while (*ptr && _add_word_sep(list, *ptr))
		++ptr;
	if (*ptr == NULL)
	{
		free(array);
		return (1);
	}
	ft_split_destroy(array);
	perror(PROGRAM_NAME);
	return (0);
}

int	lex_postexpand(t_token_list *list)
{
	t_token_list	new_list;
	t_token_node	*node;
	t_token_node	*slow;
	t_token_node	*fast;

	ft_memset(&new_list, 0, sizeof (new_list));
	node = list->first_node;
	slow = NULL;
	while (node)
	{
		fast = node->next;
		if ((slow == NULL || (slow->token & ~(RED_IN | RED_OUT)))
			&& node->token == WORD_NQ && ft_strpbrk(node->value, IFS) != NULL)
		{
			if (!_list_add_nq(&new_list, node))
				return (0);
		}
		else
		{
			__lex_add(&new_list, node);
			slow = node;
		}
		node = fast;
	}
	return (lex_concat(ft_memmove(list, &new_list, sizeof (*list))));
}
