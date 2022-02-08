/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:36:03 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 02:49:54 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

int	builtin_pwd(
	int argc __attribute__((unused)),
	char *argv[] __attribute__((unused)),
	t_env_table *env __attribute__((unused))
)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL && write(STDOUT_FILENO, cwd, ft_strlen(cwd)) >= 0)
		return (0);
	builtin_error(BUILTIN_PWD, strerror(errno));
	return (1);
}
