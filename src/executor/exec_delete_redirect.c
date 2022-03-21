/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_delete_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 22:50:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/22 00:27:13 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdlib.h>

void	exec_delete_redirect(t_exec_meta *meta)
{
	size_t		n;
	t_exec_red	*red;
	t_exec_red	*fast;

	n = 0;
	while (n < meta->count)
	{
		red = meta->exec[n].red;
		while (red)
		{
			fast = red->next;
			free(red);
			red = fast;
		}
		++n;
	}
}
