/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:07:04 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/14 18:54:07 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft.h"
#include "unistd.h"

int	builtin_echo(
	int argc __attribute__((unused)),
	char *argv[],
	t_env_table *env __attribute__((unused)))
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	while (argv[i])
	{
		if (ft_strcmp("-n", argv[i]) == 0)
		{
			nl = 0;
			++argv;
			continue ;
		}
		if (i > 1)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		++i;
	}
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
