/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_empty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 02:36:24 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/10 02:40:17 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static size_t	command_count(t_token_list *tokens)
{
	t_token_node	*node;
	size_t			count;

	node = tokens->first_node;
	count = 0;
	while (node)
	{
		if (node->token & WORD)
		{
			++count;
			while (node && node->token == WORD)
				node = node->next;
		}
		else if (node->token & (RED_IN | RED_OUT))
			node = node->next;
		if (node)
			node = node->next;
	}
	return (count);
}

int	exec_empty(t_token_list *tokens)
{
}
