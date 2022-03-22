/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 01:52:03 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/22 04:41:32 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	env_add_new(t_env_table *env, char const *key, char const *value)
{
	t_env	*entry;

	entry = env_new_entry(key, value);
	if (entry == NULL)
	{
		perror(PROGRAM_NAME);
		return (0);
	}
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
			if (entry->value != NULL)
				return (1);
			perror(PROGRAM_NAME);
			return (0);
		}
		entry = entry->next;
	}
	return (env_add_new(env, key, value));
}
