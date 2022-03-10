/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_build_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 06:13:37 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/10 07:01:03 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdlib.h>

static int	add_red(t_exec *exec, char *path, int type)
{
	t_exec_red	*red;
	t_exec_red	*iter;

	red = malloc(sizeof (*red));
	if (!red)
		return (0);
	red->path = path;
	red->type = type;
	red->next = NULL;
	if (exec->red == NULL)
		exec->red = red;
	else
	{
		iter = exec->red;
		while (iter->next)
			iter = iter->next;
		iter->next = red;
	}
	return (1);
}

// TODO deal with heredoc properly
int	exec_build_redirect(t_exec_meta *meta)
{
	t_token_list const	*list = &meta->sh->tokens;
	t_token_node		*node;
	size_t				index;

	index = 0;
	node = list->first_node;
	while (node)
	{
		if (node->token == PIPE)
			++index;
		if (node->token & (GREAT | D_GREAT | LESS))
		{
			if (!add_red(&meta->exec[index], node->next->value, node->token))
				return (0);
			node = node->next;
		}
		node = node->next;
	}
	return (1);
}
