/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_newent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:39:40 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/05 12:26:02 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type/t_env.h"
#include <stdlib.h>

t_env	*env_newent(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof (*env));
	if (env)
	{
		env->key = key;
		env->value = value;
		env->next = NULL;
	}
	return (env);
}
