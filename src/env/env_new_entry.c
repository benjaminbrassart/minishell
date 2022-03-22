/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 02:42:48 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/22 00:51:05 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

t_env	*env_new_entry(char const *key, char const *value)
{
	t_env	*env;

	env = malloc(sizeof (*env));
	if (env == NULL)
	{
		perror(PROGRAM_NAME);
		return (NULL);
	}
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	if (env->key == NULL || env->value == NULL)
	{
		free(env->key);
		free(env->value);
		free(env);
		env = NULL;
	}
	return (env);
}
