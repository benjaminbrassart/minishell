/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_from_literal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:20:21 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/22 00:50:01 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

t_env	*env_from_literal(char const *env_entry)
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
	if (env == NULL)
		perror(PROGRAM_NAME);
	return (env);
}
