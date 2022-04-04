/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 06:00:44 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 06:01:21 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "sighandler.h"
#include <stdlib.h>

void	exec_run_cleanup(t_exec_meta *meta, pid_t *pids)
{
	exec_delete_redirect(meta);
	parent_close(meta, -1);
	free(pids);
	sigint_install();
}
