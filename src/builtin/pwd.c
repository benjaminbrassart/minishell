/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:36:03 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/12 09:06:39 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

// in GNU getcwd() can be called with buf = NULL
int	pwd(int argc, char *argv[], char *env[])
{
	char	*wd;
	int		errnum;

	wd = getcwd(NULL, 0);
	if (wd)
	{
		write(1, wd, ft_strlen(wd));
		return (0);
	}
	errnum = errno;
	wd = strerror(errnum);
	write(2, wd, ft_strlen(wd));
	return (errnum);
}
