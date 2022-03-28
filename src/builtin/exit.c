/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:06:36 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/28 13:38:21 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft.h"
#include "status.h"
#include "type/t_sh.h"
#include "utils.h"
#include <errno.h>
#include <unistd.h>

static int	parse_exit_status(char const *arg, int *st_ptr)
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
	n = 0;
	while (ft_isdigit(arg[n]))
	{
		prev = value;
		value = value * 10 + arg[n++] - '0';
		if (value < prev)
			return (0);
	}
	if (arg[n] != '\0' || (n == 0 && value == 0))
		return (0);
	*st_ptr = value * sign;
	return (1);
}

int	builtin_exit(
	int argc,
	char *argv[],
	t_env_table *env __attribute__((unused))
)
{
	int	status;

	if (argc > 2)
	{
		ft_perror(BUILTIN_EXIT, "Too many arguments");
		return (EXIT_STATUS_MINOR);
	}
	status = 0;
	if (argc == 2 && !parse_exit_status(argv[1], &status))
	{
		ft_perror(BUILTIN_EXIT, "Numeric argument required");
		status = EXIT_STATUS_MAJOR;
	}
	((t_sh *)(env->sh))->force_exit = 1;
	close(STDIN_FILENO);
	return (status);
}
