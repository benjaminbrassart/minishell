/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:20:01 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 00:21:55 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "ft.h"
#include "minishell.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

int	exec_init(t_token_list *list, t_exec_meta *meta)
{
	meta->count = command_count(list);
	meta->exec = ft_calloc(meta->count, sizeof (*meta->exec));
	if (meta->exec == NULL)
	{
		perror(PROGRAM_NAME);
		return (0);
	}
	return (1);
}
