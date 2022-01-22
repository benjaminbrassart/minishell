/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:36:19 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/12 10:49:39 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "minishell.h"
#include "type/sh.h"
#include <stdlib.h>

static void	env_addent(t_sh *sh, t_env *slow, t_env *ent)
{
	if (slow)
		slow->next = ent;
	else
		sh->env = ent;
}

int	env_set(t_sh *sh, char const *key, char const *value)
{
	t_env	*env;
	t_env	*slow;

	env = sh->env;
	slow = NULL;
	while (env)
	{
		slow = env;
		if (ft_strcmp(key, env->key) == 0)
			break ;
		env = env->next;
	}
	if (!env)
	{
		env = env_newent(key, value);
		if (!env)
			return (0);
		env_addent(sh, slow, env);
	}
	else
	{
		free(env->value);
		env->value = value;
	}
	return (1);
}
