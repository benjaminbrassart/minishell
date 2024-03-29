/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:53:02 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/02 15:56:26 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "env.h"
#include "ft.h"
#include "minishell.h"
#include "status.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static int	env_buffer_append(t_env_table *env, t_buffer *buffer, char const *s,
int n)
{
	char	*env_val;

	env_val = env_getn(env, s, n);
	if (env_val)
		return (buffer_append(buffer, env_val));
	return (1);
}

static int	status_buffer_append(t_buffer *buffer)
{
	char	*s;
	int		res;

	s = ft_itoa(g_exit_status);
	if (s == NULL)
	{
		perror(PROGRAM_NAME);
		return (0);
	}
	res = buffer_append(buffer, s);
	free(s);
	return (res);
}

static int	append(t_buffer *buffer, t_env_table *env, char const **s, int n)
{
	if (n == 0)
	{
		if (**s == '?')
		{
			++*s;
			if (!status_buffer_append(buffer))
				return (0);
		}
		else if (!buffer_cappend(buffer, '$'))
			return (0);
	}
	else if (!env_buffer_append(env, buffer, *s, n))
		return (0);
	return (1);
}

char	*str_expand(t_env_table *env, char const *s)
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
		if (!append(&buffer, env, &s, n))
			return (buffer_delete(&buffer), NULL);
		s += n;
	}
	buffer_flush(&buffer);
	return (buffer.buf);
}
