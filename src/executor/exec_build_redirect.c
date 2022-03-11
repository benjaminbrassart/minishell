/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_build_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 06:13:37 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/11 08:08:31 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdlib.h>

static int	add_red(t_exec *exec, char *path, int type, int hd_index)
{
	t_exec_red	*red;
	t_exec_red	*iter;

	red = malloc(sizeof (*red));
	if (!red)
		return (0);
	red->path = path;
	red->type = type;
	red->hd_idx = hd_index;
	red->next = NULL;
	red->fd = -1;
	red->exec = exec;
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
	size_t				i;
	int					hd_index;

	i = 0;
	hd_index = 0;
	node = list->first_node;
	while (node)
	{
		if (node->token == PIPE)
			++i;
		else if (node->token & (RED_OUT | LESS))
		{
			if (!add_red(&meta->exec[i], node->next->value, node->token, -1))
				return (0);
			node = node->next;
		}
		else if (node->token == D_LESS)
		{
			if (!add_red(&meta->exec[i], NULL, D_LESS, hd_index++))
				return (0);
			node = node->next;
		}
		if (node)
			node = node->next;
	}
	return (1);
}
