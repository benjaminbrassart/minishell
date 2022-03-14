/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_heredoc_delete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 06:03:43 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/10 08:22:11 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "heredoc.h"
#include <stdlib.h>

void	lex_heredoc_delete(t_heredoc *heredoc)
{
	size_t	n;

	n = 0;
	while (n < heredoc->count)
		buffer_delete(&heredoc->buffers[n++].buffer);
	free(heredoc->buffers);
	heredoc->buffers = 0;
	heredoc->count = 0;
}
