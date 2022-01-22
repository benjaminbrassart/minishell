/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:32:01 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/12 11:33:46 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include <stdlib.h>

void	env_destroy(t_sh *sh)
{
	t_env	*env;
	t_env	*fast;

	env = sh->env;
	while (env)
	{
		fast = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = fast;
	}
	sh->env = NULL;
}
