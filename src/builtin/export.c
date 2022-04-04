/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:09:09 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 11:38:44 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "ft.h"
#include "status.h"
#include "utils.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static int	is_var_name(char const *s)
{
	int	n;

	n = 0;
	while (s[n] && s[n] != '=')
	{
		if ((!ft_isalnum(s[n]) && s[n] != '_') || (n == 0 && ft_isdigit(s[n])))
			return (0);
		++n;
	}
	return (n > 0);
}

static void	export_var(t_env_table *env, char *entry, int *res_ptr)
{
	int	n;

	n = 0;
	while (entry[n] && entry[n] != '=')
		++n;
	if (entry[n] == 0)
		return ;
	entry[n] = 0;
	if (!env_set(env, entry, entry + n + 1))
	{
		*res_ptr = EXIT_STATUS_MAJOR;
		ft_perror(BUILTIN_EXPORT, strerror(errno));
	}
}

int	builtin_export(int argc, char *argv[], t_env_table *env)
{
	int	i;
	int	res;

	if (argc < 2)
	{
		ft_perror(BUILTIN_EXPORT, "Not enough arguments");
		return (g_exit_status = EXIT_STATUS_MINOR);
	}
	res = 0;
	i = 1;
	while (i < argc)
	{
		if (!is_var_name(argv[i]))
		{
			if (EXIT_STATUS_MINOR > res)
				res = EXIT_STATUS_MINOR;
			ft_paerror(BUILTIN_EXPORT, argv[i], "Not a valid identifier");
		}
		else
			export_var(env, argv[i], &res);
		++i;
	}
	return (g_exit_status = res);
}
