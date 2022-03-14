/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:53:17 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/10 15:48:42 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdlib.h>

static void	_red_delete(t_exec_red *red)
{
	t_exec_red	*fast;

	while (red)
	{
		fast = red->next;
		free(red);
		red = fast;
	}
}

void	exec_delete(t_exec_meta *meta)
{
	size_t	n;

	n = 0;
	while (n < meta->count)
		_red_delete(meta->exec[n].red);
	free(meta->exec);
	meta->exec = NULL;
	meta->count = 0;
}
