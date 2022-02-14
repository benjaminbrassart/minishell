/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:09:09 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/14 14:09:29 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "ft.h"
#include "status.h"
#include <errno.h>
#include <string.h>

static int	is_var_name(char const *s)
{
	int	n;

	n = 0;
	while (s[n] && s[n] != '=')
	{
		if (!ft_isalnum(s[n]) && s[n] != '_')
			return (0);
		if (n == 0 && ft_isdigit(s[n]))
			return (0);
		++n;
	}
	return (1);
}

int	builtin_export(int argc, char *argv[], t_env_table *env)
{
	int		i;
	int		res;
	t_env	*entry;

	if (argc < 2)
		return (builtin_error(BUILTIN_EXPORT, "not enough arguments"), 1);
	res = 0;
	i = 1;
	while (i < argc)
	{
		if (!is_var_name(argv[i]))
		{
			res = EXIT_STATUS_MINOR;
			builtin_ferror(BUILTIN_EXPORT, argv[i], "Not a valid identifier");
		}
		else
		{
			entry = env_from_literal(argv[i]);
			if (entry)
				__env_push(env, entry);
			else
			{
				builtin_error(BUILTIN_EXPORT, strerror(errno));
				res = EXIT_STATUS_MAJOR;
			}
		}
		++i;
	}
	return (res);
}
