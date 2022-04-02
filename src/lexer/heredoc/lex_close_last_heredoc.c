/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_close_last_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 19:14:49 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/02 19:21:23 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <unistd.h>

void	lex_close_last_heredoc(t_exec *exec)
{
	t_exec_red	*red;

	red = lex_get_last_heredoc(exec, 1);
	if (red && red->open)
	{
		close(red->fd);
		close(red->hd->fd);
	}
}
