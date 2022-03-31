/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 04:14:06 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/31 18:54:46 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "builtin.h"
#include "minishell.h"
#include "status.h"
#include "utils.h"
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
			return (g_exit_status = EXIT_STATUS_OK);
		ft_perror(BUILTIN_CD, strerror(errno));
	}
	else if (argc < 2)
		ft_perror(BUILTIN_CD, "Not enough arguments");
	else if (argc > 2)
		ft_perror(BUILTIN_CD, "Too many arguments");
	return (g_exit_status = EXIT_STATUS_MINOR);
}
