/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __env_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 02:21:01 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 02:51:17 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	__env_push(t_env_table *env, t_env *entry)
{
	if (env->count == 0)
		env->first_entry = entry;
	else
		env->last_entry->next = entry;
	env->last_entry = entry;
	entry->next = NULL;
	++env->count;
}
