/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 05:55:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 08:42:48 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static int	print_error(t_token_node *node)
{
	g_exit_status = LEX_SYNTAX_ERRNUM;
	return (0);
}

int	lex_check(t_token_list *list)
{
	t_token_node	*node;

	node = list->first_node;
	while (node)
	{
		if ((node == list->first_node && node->token | PIPE)
			|| (node == list->last_node && !(node->token | WORD)))
			return (print_error(node));
		node = node->next;
	}
	return (1);
}
