/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 02:10:59 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/18 17:59:57 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include <stdlib.h>

char	*env_get(t_env_table *env, char const *key)
{
	t_env	*entry;

	entry = env->first_entry;
	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
			return (entry->value);
		entry = entry->next;
	}
	return (NULL);
}

char	*env_getn(t_env_table *env, char const *key, size_t n)
{
	t_env	*entry;
	char	*new_key;

	entry = env->first_entry;
	new_key = ft_strndup(key, n);
	if (new_key == NULL)
		return (NULL);
	while (entry)
	{
		if (ft_strcmp(entry->key, new_key) == 0)
			return (free(new_key), entry->value);
		entry = entry->next;
	}
	free(new_key);
	return (NULL);
}
