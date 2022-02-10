/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:28:10 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/11 00:39:00 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

int	builtin_env(
	int argc __attribute__((unused)),
	char *argv[] __attribute__((unused)),
	t_env_table *env
)
{
	t_env	*entry;

	entry = env->first_entry;
	while (entry)
	{
		printf("%s=%s\n", entry->key, entry->value);
		entry = entry->next;
	}
	return (0);
}
