/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_dump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 00:56:47 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/10 12:26:00 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

static char	*strtoken(t_token token)
{
	if (token == WORD)
		return ("WORD");
	if (token == PIPE)
		return ("PIPE");
	if (token == LESS)
		return ("LESS");
	if (token == D_LESS)
		return ("D_LESS");
	if (token == GREAT)
		return ("GREAT");
	if (token == D_GREAT)
		return ("D_GREAT");
	if (token == SEPARATOR)
		return ("SEPARATOR");
	return ("(unknown)");
}

void	lex_dump(t_token_list *list)
{
	t_token_node	*node;

	node = list->first_node;
	while (node)
	{
		if (node->value)
			printf(" %-9s (%d) | %s\n", strtoken(node->token), node->expandable,
				node->value);
		else
			printf(" %-9s (%d) |\n", strtoken(node->token), node->expandable);
		node = node->next;
	}
}
