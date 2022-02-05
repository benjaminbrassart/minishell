/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:08:14 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/05 12:25:49 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include "type/t_env.h"
#include "type/t_sh.h"

char	*env_get(t_env *env, char const *key)
{
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			break ;
		env = env->next;
	}
	if (env)
		return (env->value);
	return (NULL);
}

char	*env_getn(t_env *env, char const *key, size_t n)
{
	while (env)
	{
		if (ft_strncmp(key, env->key, n) == 0)
			break ;
		env = env->next;
	}
	if (env)
		return (env->value);
	return (NULL);
}
