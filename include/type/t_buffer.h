/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_buffer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 12:02:44 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 03:57:16 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_BUFFER_H
# define T_BUFFER_H

# include <stddef.h>

# define STATIC_BUFFER_SIZE 2048

typedef struct s_buffer	t_buffer;

/**
 * A simple string buffer
 *
 * @param position the index in st_buf
 * @param st_buf a static buffer
 * @param length the length of buf
 * @param buf the real buffer, heap allocation
 */
struct s_buffer
{
	size_t	position;
	char	st_buf[STATIC_BUFFER_SIZE];
	size_t	length;
	char	*buf;
};

#endif
