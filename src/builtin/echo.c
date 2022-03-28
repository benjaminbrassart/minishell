/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:07:04 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/28 14:31:10 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

void	print_args(char *argv[])
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (i > 0)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		++i;
	}
}

int	builtin_echo(
	int argc __attribute__((unused)),
	char *argv[],
	t_env_table *env __attribute__((unused)))
{
	int	nl;
	int	i;
	int	j;

	nl = 1;
	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j] == 'n')
			++j;
		if (j == 1 || argv[i][j] != 0)
			break ;
		nl = 0;
		++i;
	}
	print_args(argv + i);
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
