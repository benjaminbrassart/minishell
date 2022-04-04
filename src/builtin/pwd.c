/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:36:03 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/31 18:59:16 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft.h"
#include "status.h"
#include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	builtin_pwd(
	int argc __attribute__((unused)),
	char *argv[] __attribute__((unused)),
	t_env_table *env __attribute__((unused))
)
{
	char	*cwd;
	size_t	len;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		len = ft_strlen(cwd);
		cwd[len] = '\n';
		if (write(STDOUT_FILENO, cwd, len + 1) >= 0)
		{
			free(cwd);
			return (g_exit_status = EXIT_STATUS_OK);
		}
	}
	ft_perror(BUILTIN_PWD, strerror(errno));
	return (g_exit_status = EXIT_STATUS_MINOR);
}
