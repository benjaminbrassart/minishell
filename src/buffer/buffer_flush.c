/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_flush.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:36:05 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/03 14:43:24 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "ft.h"
#include <stdlib.h>

int	buffer_flush(t_buffer *buffer)
{
	char	*new_buf;

	new_buf = malloc(buffer->length + buffer->position + 1);
	if (!new_buf)
		return (0);
	ft_memmove(new_buf, buffer->buf, buffer->length);
	ft_memmove(new_buf + buffer->length, buffer->st_buf, buffer->position);
	new_buf[buffer->length + buffer->position] = '\0';
	free(buffer->buf);
	buffer->buf = new_buf;
	return (1);
}
