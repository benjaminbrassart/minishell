/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 02:04:26 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/15 02:22:58 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft.h"
#include <stdlib.h>

void	env_unset(t_env_table *env, char const *key)
{
	t_env	*entry;
	t_env	*slow;

	entry = env->first_entry;
	slow = NULL;
	while (entry)
	{
		if (ft_strcmp(key, entry->key) == 0)
		{
			free(entry->key);
			free(entry->value);
			if (slow == NULL)
				env->first_entry = entry->next;
			else
				slow->next = entry->next;
			free(entry);
			--env->count;
			return ;
		}
		slow = entry;
		entry = entry->next;
	}
}
