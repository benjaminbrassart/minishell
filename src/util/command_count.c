/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:38:33 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/18 16:12:01 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	command_count(t_token_list *list)
{
	t_token_node	*node;
	size_t			n;

	node = list->first_node;
	n = 0;
	while (node)
	{
		while (node && (node->token & (RED_IN | RED_OUT)))
			node = node->next->next;
		if (node)
		{
			if (n == 0 && (node->token & WORD))
				++n;
			if (node->token == PIPE)
				++n;
			node = node->next;
		}
	}
	return (n);
}
