/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_get_last_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:46:42 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/02 18:05:43 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "heredoc.h"
#include "token.h"
#include <unistd.h>

t_exec_red	*lex_get_last_heredoc(t_exec *exec, int skip_simple)
{
	t_exec_red	*red;
	t_exec_red	*last;

	red = exec->red;
	last = NULL;
	while (red)
	{
		if (red->type == D_LESS)
			last = red;
		else if (red->type == LESS && !skip_simple)
			last = NULL;
		red = red->next;
	}
	return (last);
}
