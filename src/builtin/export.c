/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:09:09 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 02:50:29 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "ft.h"

static int	is_var_name(char const *s)
{
	int	n;

	n = 0;
	while (s[n])
	{
		if (!ft_isalnum(s[n]) && s[n] != '_')
			return (0);
		if (n == 0 && ft_isdigit(s[n]))
			return (0);
		++n;
	}
	return (1);
}

int	builtin_export(
	int argc,
	char *argv[],
	t_env_table *env __attribute__((unused))
)
{
	int	i;
	int	res;

	if (argc < 2)
		return (builtin_error(BUILTIN_EXPORT, "not enough arguments"), 1);
	res = 0;
	i = 1;
	while (i < argc)
	{
		if (!is_var_name(argv[i]))
		{
			res = 1;
			builtin_ferror(BUILTIN_EXPORT, argv[i], "not a valid identifier");
		}
		else
		{
		}
	}
	return (res);
}
