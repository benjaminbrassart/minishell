/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:53:17 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/14 09:53:54 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdlib.h>

void	exec_delete(t_exec_meta *meta)
{
	free(meta->exec);
	meta->exec = NULL;
	meta->count = 0;
}
