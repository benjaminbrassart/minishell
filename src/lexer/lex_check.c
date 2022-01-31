/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 05:55:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/22 07:25:57 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

// FIXME magic value
static int	print_error(t_token_node *node)
{
	g_exit_status = 2;
	return (0);
}

static int	is_word(t_token token)
{
	return (token == WORD_DQ || token == WORD_NQ || token == WORD_SQ);
}

int	lex_check(t_token_list *list)
{
	t_token_node	*node;

	node = list->first_node;
	while (node)
	{
		if ((node == list->first_node && node->token == PIPE)
			|| (node == list->last_node && !is_word(node->token)))
			return (print_error(node));
		node = node->next;
	}
	return (1);
}
