/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 02:15:14 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 02:51:27 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include <stdlib.h>

static t_env	*extract_node(char const *env_entry)
{
	t_env	*env;
	size_t	i;

	env = malloc(sizeof (*env));
	if (env)
	{
		i = ft_strcspn(env_entry, "=");
		env->key = ft_strndup(env_entry, i);
		env->value = ft_strdup(env_entry + i + 1);
		env->next = NULL;
		if (!env->key || !env->value)
		{
			free(env->key);
			free(env->value);
			free(env);
			env = NULL;
		}
	}
	return (env);
}

int	env_init(t_env_table *env, char *envp[])
{
	int		n;
	t_env	*entry;

	n = 0;
	while (envp[n])
	{
		entry = extract_node(envp[n]);
		if (entry == NULL)
			return (0);
		__env_push(env, entry);
		++n;
	}
	return (1);
}
