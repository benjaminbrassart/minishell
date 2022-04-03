/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 05:15:06 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/03 05:18:33 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	set_shlvl(t_env_table *env)
{
	char	*shlvl_var;
	char	*end;
	int		shlvl;
	int		res;

	shlvl_var = env_get(env, "SHLVL");
	shlvl = 0;
	if (shlvl_var)
	{
		shlvl = ft_strtoi(shlvl_var, &end);
		if (shlvl_var == end || *end != 0)
			shlvl = 0;
	}
	res = 0;
	shlvl_var = ft_itoa(++shlvl);
	if (shlvl_var)
	{
		res = env_set(env, "SHLVL", shlvl_var);
		free(shlvl_var);
	}
	if (!res)
		perror(PROGRAM_NAME);
	return (res);
}
