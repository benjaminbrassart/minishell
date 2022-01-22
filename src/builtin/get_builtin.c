/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:38:56 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/19 19:40:23 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft.h"

t_builtin	*get_builtin(char const *name)
{
	size_t	i;

	i = 0;
	while (i < sizeof (name))
	{
		if (ft_strcmp(g_builtins[i].name, name) == 0)
			return (&g_builtins[i]);
		++i;
	}
	return (NULL);
}
