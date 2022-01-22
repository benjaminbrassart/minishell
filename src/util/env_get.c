/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:08:14 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/12 10:51:06 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "type/env.h"
#include "type/sh.h"

char	*env_get(t_sh *sh, char const *key)
{
	t_env	*env;

	env = sh->env;
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			break ;
		env = env->next;
	}
	if (env)
		return (env->key);
	return (NULL);
}
