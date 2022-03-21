/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 02:15:14 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/21 23:27:12 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	env_init(t_env_table *env, char *envp[])
{
	int		n;
	t_env	*entry;

	n = 0;
	while (envp[n])
	{
		entry = env_from_literal(envp[n]);
		if (entry == NULL)
		{
			perror(PROGRAM_NAME);
			return (0);
		}
		__env_push(env, entry);
		++n;
	}
	return (1);
}
