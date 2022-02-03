/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:51:21 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/03 20:54:26 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "environ.h"
#include "expander.h"
#include "ft.h"
#include "status.h"
#include "type/sh.h"
#include <stdio.h>

static int	env_buffer_append(t_sh *sh, t_buffer *buffer, char const *s, int n)
{
	char	*env_val;

	env_val = env_getn(sh, s, n);
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

char	*exp_expand(t_sh *sh, char const *s)
{
	char		*new_s;
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
		else if (!env_buffer_append(sh, &buffer, s, n))
			return (buffer_delete(&buffer), NULL);
		s += n;
	}
	buffer_flush(&buffer);
	new_s = ft_strdup(buffer.buf);
	buffer_delete(&buffer);
	return (new_s);
}
