/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:40:55 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 13:27:53 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

void	lex_delete(t_token_list *list)
{
	t_token_node	*node;
	t_token_node	*fast;

	node = list->first_node;
	while (node)
	{
		fast = node->next;
		free(node->value);
		free(node);
		node = fast;
	}
	list->first_node = NULL;
	list->last_node = NULL;
	list->length = 0;
}
