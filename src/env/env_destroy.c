/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 01:47:46 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 01:51:54 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

void	env_destroy(t_env_table *env)
{
	t_env	*entry;
	t_env	*fast;

	entry = env->first_entry;
	while (entry)
	{
		fast = entry->next;
		free(entry->key);
		free(entry->value);
		free(entry);
		entry = fast;
	}
	env->first_entry = NULL;
	env->last_entry = NULL;
	env->count = 0;
}
