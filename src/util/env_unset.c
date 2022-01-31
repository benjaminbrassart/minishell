/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:29:27 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 09:36:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "ft.h"
#include <stdlib.h>

void	env_unset(t_sh *sh, char const *key)
{
	t_env	*env;
	t_env	*slow;

	env = sh->env;
	slow = NULL;
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			if (slow)
				slow->next = env->next;
			else
				sh->env = env->next;
			free(env->key);
			free(env->value);
			free(env);
			break ;
		}
		slow = env;
		env = env->next;
	}
}
