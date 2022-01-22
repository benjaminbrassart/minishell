/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 05:55:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/21 06:13:22 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdio.h>

// FIXME magic value
static int	print_error(t_token_node *node)
{
	g_exit_status = 2;
	return (0);
}

int	lex_check(t_token_list *list)
{
	t_token_node	*node;

	node = list->first_node;
	while (node)
	{
		if (node->token == PIPE && node == list->first_node)
			return (print_error(node));

		node = node->next;
	}
}
