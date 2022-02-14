/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:06:36 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/14 14:08:21 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft.h"
#include "status.h"
#include <errno.h>
#include <unistd.h>

static int	get_exit_status(char const *arg)
{
	int	n;
	int	sign;
	int	value;
	int	prev;

	value = 0;
	sign = 1;
	if (*arg == '+' || *arg == '-')
		if (*arg++ == '-')
			sign = -1;
	while (ft_isdigit(arg[n]))
	{
		prev = value;
		value = value * 10 + arg[n++] - '0';
		if (value < prev)
			return (0);
	}
	if (arg[n] != '\0' || (n == 0 && value == 0))
		return (0);
	g_exit_status = value * sign;
	return (1);
}

int	builtin_exit(
	int argc,
	char *argv[],
	t_env_table *env __attribute__((unused))
)
{
	if (argc > 2)
	{
		builtin_error(BUILTIN_EXIT, "Too many arguments");
		return (EXIT_STATUS_MINOR);
	}
	if (argc == 2 && !get_exit_status(argv[1]))
	{
		builtin_error(BUILTIN_EXIT, "Numeric argument required");
		g_exit_status = EXIT_STATUS_MAJOR;
	}
	close(STDIN_FILENO);
	return (0);
}
