/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:29:09 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 03:44:35 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include "type/t_buffer.h"
# include <stddef.h>

/**
 * Initialize a buffer
 */
void	buffer_init(t_buffer *buffer);

/**
 * Append a string to a buffer
 */
int		buffer_append(t_buffer *buffer, char const *s);

/**
 * Append the n first character of a string
 */
int		buffer_nappend(t_buffer *buffer, char const *s, size_t n);

/**
 * Append a character to a buffer
 */
int		buffer_cappend(t_buffer *buffer, char c);

/**
 * Force the reallocation of a buffer
 */
int		buffer_flush(t_buffer *buffer);

/**
 * Delete a buffer
 */
void	buffer_delete(t_buffer *buffer);

#endif
