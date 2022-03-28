/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:38:33 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/28 11:40:06 by bbrassar         ###   ########.fr       */
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
		if (n == 0)
			++n;
		if (node->token & PIPE)
			++n;
		node = node->next;
	}
	return (n);
}
