/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 04:14:06 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/14 14:08:17 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "builtin.h"
#include "minishell.h"
#include "status.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

int	builtin_cd(
	int argc,
	char *argv[],
	t_env_table *env __attribute__((unused))
)
{
	if (argc == 2)
	{
		if (chdir(argv[1]) == 0)
			return (EXIT_STATUS_OK);
		builtin_error(BUILTIN_CD, strerror(errno));
	}
	else if (argc < 2)
		builtin_error(BUILTIN_CD, "Not enough arguments");
	else if (argc > 2)
		builtin_error(BUILTIN_CD, "Too many arguments");
	return (EXIT_STATUS_MINOR);
}
