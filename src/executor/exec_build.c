/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 07:15:09 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/18 10:18:57 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "executor.h"
#include "ft.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static size_t	count_commands(t_token_list *list)
{
	t_token_node	*node;
	size_t			n;

	node = list->first_node;
	n = 0;
	while (node)
	{
		if (n == 0 && (node->token & WORD))
			++n;
		if (node->token == PIPE)
			++n;
		node = node->next;
	}
	return (n);
}

static size_t	count_argc(t_token_node *node)
{
	size_t	n;

	n = 0;
	while (node && node->token == WORD)
	{
		++n;
		node = node->next;
	}
	return (n);
}

static int	copy_argv(t_token_node **node, t_exec *exec)
{
	size_t			n;

	exec->fd_out = STDOUT_FILENO;
	while (*node)
	{
		if ((*node)->token == WORD)
			break ;
		if ((*node)->token & (RED_IN | RED_OUT))
			*node = (*node)->next;
		*node = (*node)->next;
	}
	exec->argc = count_argc(*node);
	exec->argv = ft_calloc(exec->argc + 1, sizeof (*exec->argv));
	n = 0;
	if (!exec->argv)
		return (0);
	while (n < exec->argc)
	{
		exec->argv[n] = (*node)->value;
		*node = (*node)->next;
		++n;
	}
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
	else if (ft_strchr(exec->argv[0], '/'))
	{
		if (access(exec->argv[0], X_OK) == 0)
			exec->interface.path = exec->argv[0];
		else
			builtin_error(exec->argv[0], strerror(errno));
	}
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

	meta_p->count = count_commands(list);
	if (meta_p->count == 0)
		return (1);
	meta_p->exec = ft_calloc(meta_p->count, sizeof (*meta_p->exec));
	if (!meta_p->exec)
		return (0);
	n = 0;
	node = list->first_node;
	while (n < meta_p->count)
	{
		meta_p->exec[n].meta = meta_p;
		if (!copy_argv(&node, &meta_p->exec[n]))
			return (0);
		set_path(&meta_p->exec[n++]);
	}
	return (exec_pipe(meta_p));
}
