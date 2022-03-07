/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:07:04 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/14 11:35:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft.h"
#include "unistd.h"

int	builtin_echo(
	int argc,
	char *argv[],
	t_env_table *env __attribute__((unused)))
{
	int			i;
	int			newline;

	i = 1;
	newline = 1;
	while (i < argc)
	{
		if (i == 1 && ft_strcmp(argv[i], "-n") == 0)
		{
			newline = 0;
			++i;
			continue ;
		}
		if (i != (1 + !newline) && write(STDOUT_FILENO, " ", 1) < 0)
			return (1);
		if (write(STDOUT_FILENO, argv[i], ft_strlen(argv[i])) < 0)
			return (1);
		++i;
	}
	if (newline && write(STDOUT_FILENO, "\n", 1) < 0)
		return (1);
	return (0);
}
