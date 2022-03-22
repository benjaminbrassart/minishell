/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_toarray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 05:50:51 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/22 04:55:10 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "env.h"
#include "ft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	_append_buf(t_buffer *buffer, t_env *node)
{
	buffer_init(buffer);
	return (buffer_append(buffer, node->key)
		&& buffer_cappend(buffer, '=')
		&& buffer_append(buffer, node->value)
		&& buffer_flush(buffer));
}

char	**env_toarray(t_env_table *env)
{
	t_buffer	buffer;
	char		**envp;
	t_env		*node;
	size_t		n;

	envp = ft_calloc(env->count + 1, sizeof (*envp));
	if (envp == NULL)
	{
		perror(PROGRAM_NAME);
		return (NULL);
	}
	node = env->first_entry;
	n = 0;
	while (node != NULL)
	{
		if (!_append_buf(&buffer, node))
			return (buffer_delete(&buffer), ft_split_destroy(envp));
		envp[n++] = buffer.buf;
		node = node->next;
	}
	return (envp);
}
