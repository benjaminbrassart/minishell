/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_heredoc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 05:50:54 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/11 06:52:56 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_HEREDOC_H
# define T_HEREDOC_H

# include "type/t_buffer.h"

typedef struct s_heredoc_buffer	t_heredoc_buffer;
typedef struct s_heredoc		t_heredoc;

struct s_heredoc_buffer
{
	t_buffer	buffer;
	char		*delimiter;
	int			fd;
};

struct s_heredoc
{
	t_heredoc_buffer	*buffers;
	size_t				count;
};

#endif
