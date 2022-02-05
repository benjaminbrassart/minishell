/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:29:09 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 00:51:24 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include "type/t_buffer.h"
# include <stddef.h>

void	buffer_init(t_buffer *buffer);

int		buffer_append(t_buffer *buffer, char const *s);

int		buffer_nappend(t_buffer *buffer, char const *s, size_t n);

int		buffer_cappend(t_buffer *buffer, char c);

int		buffer_flush(t_buffer *buffer);

void	buffer_delete(t_buffer *buffer);

#endif
