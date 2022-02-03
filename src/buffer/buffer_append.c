/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:35:16 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/03 15:59:14 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

int	buffer_cappend(t_buffer *buffer, char c)
{
	if (buffer->position >= STATIC_BUFFER_SIZE && !buffer_flush(buffer))
		return (0);
	buffer->st_buf[buffer->position++] = c;
	return (1);
}

int	buffer_nappend(t_buffer *buffer, char const *s, size_t n)
{
	while (n-- && *s)
		if (!buffer_cappend(buffer, *s++))
			return (0);
	return (1);
}

int	buffer_append(t_buffer *buffer, char const *s)
{
	while (*s)
		if (!buffer_cappend(buffer, *s++))
			return (0);
	return (1);
}
