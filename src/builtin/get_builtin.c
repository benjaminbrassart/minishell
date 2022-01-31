/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:38:56 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 04:43:05 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft.h"

t_builtin	*get_builtin(char const *name)
{
	size_t	i;
	int		res;

	i = 0;
	while (i < (sizeof (g_builtins) / sizeof (g_builtins[0])))
	{
		res = ft_strcmp(g_builtins[i].name, name);
		if (res == 0)
			return (&g_builtins[i]);
		++i;
	}
	return (NULL);
}
