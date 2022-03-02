/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:05:50 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/15 03:11:45 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "ft.h"
#include "status.h"

static int	is_var_name(char const *s)
{
	if (*s != '_' && !ft_isalpha(*s))
		return (0);
	++s;
	while (*s == '_' || ft_isalnum(*s))
		++s;
	return (*s == 0);
}

int	builtin_unset(
	int argc,
	char *argv[],
	t_env_table *env
)
{
	int	n;
	int	res;

	n = 1;
	res = EXIT_STATUS_OK;
	while (n < argc)
	{
		if (is_var_name(argv[n]))
			env_unset(env, argv[n]);
		else
			builtin_aerror(BUILTIN_UNSET, argv[n], "Not a valid identifier");
		++n;
	}
	return (res);
}
