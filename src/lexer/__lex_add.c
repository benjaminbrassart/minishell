/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __lex_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 04:59:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/11 04:59:21 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	__lex_add(t_token_list *list, t_token_node *node)
{
	if (list->length == 0)
		list->first_node = node;
	else
		list->last_node->next = node;
	list->last_node = node;
	++list->length;
}
