/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_postexpand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:07:28 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/02 22:22:21 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void	list_add(t_token_list *list, t_token_node *node)
{
	if (list->length == 0)
		list->first_node = node;
	else
		list->last_node->next = node;
	node->next = NULL;
	list->last_node = node;
	++(list->length);
}

static t_token_node	*fill_node(t_token_node *node, char *s)
{
	if (s == NULL)
		node->token = SEPARATOR;
	else
		node->token = WORD_NQ;
	node->value = s;
	return (node);
}

static int	list_add_nq(t_token_list *list, t_token_node *node)
{
	char			**array;
	t_token_node	*new_node;
	int				n;

	array = ft_split(node->value, ' ');
	free(node);
	if (array == NULL)
	{
		perror(PROGRAM_NAME);
		return (0);
	}
	n = 0;
	while (array[n])
	{
		new_node = malloc(sizeof (*new_node));
		if (!new_node)
			return (ft_split_destroy(array), perror(PROGRAM_NAME), 0);
		list_add(list, fill_node(new_node, array[n++]));
		new_node = malloc(sizeof (*new_node));
		if (!new_node)
			return (ft_split_destroy(array), perror(PROGRAM_NAME), 0);
		list_add(list, fill_node(new_node, NULL));
	}
	return (1);
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
		if ((node->token & WORD_NQ) && slow
			&& (slow->token & ~(RED_IN | RED_OUT))
			&& ft_strchr(node->value, ' ') != NULL)
		{
			if (!list_add_nq(&new_list, node))
				return (0);
		}
		else
			list_add(&new_list, node);
		slow = node;
		node = fast;
	}
	return (lex_concat(list));
}
