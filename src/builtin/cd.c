/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 04:14:06 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 02:49:37 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "builtin.h"
#include "minishell.h"
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
		if (chdir(argv[1]) != 0)
			return (builtin_error(BUILTIN_CD, strerror(errno)), 1);
		return (0);
	}
	if (argc < 2)
		builtin_error(BUILTIN_CD, "not enough arguments");
	else
		builtin_error(BUILTIN_CD, "too many arguments");
	return (1);
}
