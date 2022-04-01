/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:28:10 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/31 18:55:22 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "status.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

int	builtin_env(
	int argc __attribute__((unused)),
	char *argv[] __attribute__((unused)),
	t_env_table *env
)
{
	t_env	*entry;

	if (argc != 1)
	{
		ft_perror(BUILTIN_ENV, "Too many arguments");
		return (g_exit_status = EXIT_STATUS_MINOR);
	}
	entry = env->first_entry;
	while (entry)
	{
		printf("%s=%s\n", entry->key, entry->value);
		entry = entry->next;
	}
	return (g_exit_status = 0);
}
