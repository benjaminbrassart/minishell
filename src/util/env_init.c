/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:21:24 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/22 12:17:16 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "ft.h"
#include <stdlib.h>

static t_env	*extract_node(char *env_entry)
{
	t_env	*env;
	int		i;

	env = malloc(sizeof (*env));
	if (env)
	{
		i = 0;
		while (env_entry[i] && env_entry[i] != '=')
			++i;
		if (!env_entry[i])
			return (NULL);
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

int	env_init(t_sh *sh, char *ev[])
{
	t_env	*last;
	t_env	*node;
	int		i;

	last = NULL;
	i = -1;
	while (ev[++i])
	{
		node = extract_node(ev[i]);
		if (!node)
			return (0);
		if (last)
			last->next = node;
		else
			sh->env = node;
		last = node;
	}
	return (1);
}
