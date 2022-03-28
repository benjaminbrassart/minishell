/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 05:21:17 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/28 12:50:22 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "executor.h"
#include "heredoc.h"
#include "lexer.h"
#include <stdlib.h>
#include <unistd.h>

void	close_fds(t_exec_meta *meta)
{
	size_t	n;

	n = 0;
	while (n < meta->count)
	{
		if (meta->exec[n].fd_in != STDIN_FILENO)
			close(meta->exec[n].fd_in);
		if (meta->exec[n].fd_out != STDOUT_FILENO)
			close(meta->exec[n].fd_out);
		++n;
	}
}

void	parent_close(t_exec_meta *meta, int index)
{
	size_t	n;

	n = 0;
	while (n < meta->count)
	{
		if (index < 0 || (size_t)index != n)
		{
			free(meta->exec[n].argv);
			if (meta->exec[n].search_path)
				free(meta->exec[n].interface.path);
		}
		++n;
	}
	if (index < 0)
		free(meta->exec);
}

void	child_destroy(t_exec *exec)
{
	close_fds(exec->meta);
	env_destroy(&exec->meta->sh->env);
	lex_delete(&exec->meta->sh->tokens);
	exec_delete_redirect(exec->meta);
	parent_close(exec->meta, (int)(exec - exec->meta->exec));
	lex_heredoc_delete(&exec->meta->sh->heredoc);
	free(exec->argv);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	if (!exec->is_builtin)
		free(exec->interface.path);
	free(exec->meta->exec);
}
