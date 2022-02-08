/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:51:21 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 03:31:42 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "env.h"
#include "expander.h"
#include "ft.h"
#include "status.h"
#include "type/t_sh.h"
#include <stdio.h>

static int	env_buffer_append(t_env_table *env, t_buffer *buffer, char const *s,
int n)
{
	char	*env_val;

	env_val = env_getn(env, s, n);
	if (env_val)
		return (buffer_append(buffer, env_val));
	return (1);
}

static int	st_buffer_append(t_buffer *buffer)
{
	char				*s;

	s = ft_itoa(g_exit_status);
	return (buffer_append(buffer, s));
}

char	*exp_expand(t_env_table *env, char const *s)
{
	t_buffer	buffer;
	int			n;

	buffer_init(&buffer);
	while (1)
	{
		while (*s != '\0' && *s != '$')
			buffer_cappend(&buffer, *s++);
		if (*s++ == '\0')
			break ;
		n = 0;
		while (s[n] && (s[n] == '_' || ft_isalnum(s[n])))
			++n;
		if (n == 0)
		{
			if (*s == '?')
			{
				if (!st_buffer_append(&buffer))
					return (buffer_delete(&buffer), NULL);
				++s;
			}
			else if (!buffer_cappend(&buffer, '$'))
				return (buffer_delete(&buffer), NULL);
		}
		else if (!env_buffer_append(env, &buffer, s, n))
			return (buffer_delete(&buffer), NULL);
		s += n;
	}
	buffer_flush(&buffer);
	return (buffer.buf);
}
