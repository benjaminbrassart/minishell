/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 01:52:03 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 02:45:34 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include <stdlib.h>

static int	env_add_new(t_env_table *env, char const *key, char const *value)
{
	t_env	*entry;

	entry = env_new_entry(key, value);
	if (entry == NULL)
		return (0);
	__env_push(env, entry);
	return (1);
}

int	env_set(t_env_table *env, char const *key, char const *value)
{
	t_env	*entry;

	entry = env->first_entry;
	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
		{
			free(entry->value);
			entry->value = ft_strdup(value);
			return (entry->value != NULL);
		}
		entry = entry->next;
	}
	return (env_add_new(env, key, value));
}
