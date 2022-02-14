/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_toarray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 05:50:51 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/14 13:40:05 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "env.h"
#include "ft.h"
#include <stdlib.h>

char	**env_toarray(t_env_table *env)
{
	t_buffer	buffer;
	char		**envp;
	t_env		*node;
	size_t		n;

	envp = ft_calloc(env->count + 1, sizeof (*envp));
	if (!envp)
		return (NULL);
	node = env->first_entry;
	n = 0;
	while (node != NULL)
	{
		buffer_init(&buffer);
		if (!buffer_append(&buffer, node->key) || !buffer_cappend(&buffer, '=')
			|| !buffer_append(&buffer, node->value) || !buffer_flush(&buffer))
		{
			buffer_delete(&buffer);
			return (ft_split_destroy(envp));
		}
		envp[n++] = buffer.buf;
		node = node->next;
	}
	return (envp);
}
