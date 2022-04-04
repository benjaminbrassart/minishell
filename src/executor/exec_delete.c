/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:53:17 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/02 20:31:04 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdlib.h>

void	exec_delete(t_exec_meta *meta)
{
	exec_delete_redirect(meta);
	free(meta->exec);
	meta->exec = NULL;
	meta->count = 0;
}
