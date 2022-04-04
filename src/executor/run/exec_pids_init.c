/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pids_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:15:34 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 00:18:13 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

pid_t	*exec_pids_init(t_exec_meta *meta)
{
	pid_t	*pids;

	pids = malloc(sizeof (*pids) * meta->count);
	if (!pids)
		perror(PROGRAM_NAME);
	return (pids);
}
