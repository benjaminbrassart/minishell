/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 07:15:09 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 02:48:26 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "executor.h"
#include "ft.h"
#include "minishell.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static size_t	count_argc(t_token_node *node)
{
	size_t	n;

	n = 0;
	while (node)
	{
		if (node->token == PIPE)
			break ;
		if (node->token & (RED_IN | RED_OUT))
		{
			node = node->next->next;
			continue ;
		}
		node = node->next;
		++n;
	}
	return (n);
}

static void	_skip_red(t_token_node **node, t_exec *exec)
{
	size_t	n;

	n = 0;
	while (n < exec->argc)
	{
		if (*node)
		{
			exec->argv[n] = (*node)->value;
			*node = (*node)->next;
			++n;
		}
		while (*node && (*node)->token & (RED_IN | RED_OUT))
			*node = (*node)->next->next;
	}
}

static int	copy_argv(t_token_node **node, t_exec *exec)
{
	while (*node && ((*node)->token & (RED_IN | RED_OUT)))
		*node = (*node)->next->next;
	exec->argc = count_argc(*node);
	exec->argv = ft_calloc(exec->argc + 1, sizeof (*exec->argv));
	if (exec->argv == NULL)
	{
		perror(PROGRAM_NAME);
		return (0);
	}
	_skip_red(node, exec);
	return (1);
}

static void	set_path(t_exec *exec)
{
	t_builtin	*builtin;

	builtin = get_builtin(exec->argv[0]);
	if (builtin)
	{
		exec->is_builtin = 1;
		exec->interface.builtin = builtin->fn;
	}
	else if (ft_strchr(exec->argv[0], '/') != NULL)
		exec->interface.path = exec->argv[0];
	else
	{
		exec->search_path = 1;
		exec->interface.path = path_search(&exec->meta->sh->env, exec->argv[0]);
	}
}

int	exec_build(t_token_list *list, t_exec_meta *meta_p)
{
	t_token_node	*node;
	size_t			n;

	if (!exec_init(list, meta_p))
		return (0);
	n = 0;
	node = list->first_node;
	while (n < meta_p->count)
	{
		meta_p->exec[n].fd_in = STDIN_FILENO;
		meta_p->exec[n].fd_out = STDOUT_FILENO;
		meta_p->exec[n].meta = meta_p;
		meta_p->exec[n].index = n;
		if (node->token == PIPE)
			node = node->next;
		if (!copy_argv(&node, &meta_p->exec[n]))
			return (0);
		if (meta_p->exec[n].argc > 0)
			set_path(&meta_p->exec[n]);
		++n;
	}
	return (exec_build_redirect(meta_p));
}
