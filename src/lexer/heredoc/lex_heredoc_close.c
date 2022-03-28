/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_heredoc_close.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:37:54 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/28 12:40:42 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <unistd.h>

void	lex_heredoc_close(t_exec *exec)
{
	t_exec_red	*red;

	red = exec->red;
	while (red)
	{
		close(exec->meta->sh->heredoc.buffers[red->hd_idx].fd);
		red = red->next;
	}
}
