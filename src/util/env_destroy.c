/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:32:01 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/05 12:09:41 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

void	env_destroy(t_env **env_p)
{
	t_env	*env;
	t_env	*fast;

	env = *env_p;
	while (env)
	{
		fast = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = fast;
	}
	*env_p = NULL;
}
