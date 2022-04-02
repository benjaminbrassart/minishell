/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_heredoc_close.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:37:54 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/02 21:02:15 by bbrassar         ###   ########.fr       */
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
		if (red->hd && red->hd->open)
		{
			close(red->fd);
			close(red->hd->fd);
			red->hd->open = 0;
		}
		red = red->next;
	}
	exec->red = NULL;
}
