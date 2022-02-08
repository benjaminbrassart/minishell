/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 00:48:06 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 03:26:42 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "builtin.h"
#include "minishell.h"
#include <unistd.h>

void	builtin_error(char const *name, char const *msg)
{
	t_buffer	buffer;

	buffer_init(&buffer);
	if (buffer_append(&buffer, PROGRAM_NAME ": ")
		&& buffer_append(&buffer, name)
		&& buffer_append(&buffer, ": ")
		&& buffer_append(&buffer, msg)
		&& buffer_append(&buffer, "\n")
		&& buffer_flush(&buffer))
		write(STDERR_FILENO, buffer.buf, buffer.length);
	buffer_delete(&buffer);
}

void	builtin_ferror(char const *name, char const *file, char const *msg)
{
	t_buffer	buffer;

	buffer_init(&buffer);
	if (buffer_append(&buffer, PROGRAM_NAME ": ")
		&& buffer_append(&buffer, name)
		&& buffer_append(&buffer, ": ")
		&& buffer_append(&buffer, file)
		&& buffer_append(&buffer, ": ")
		&& buffer_append(&buffer, msg)
		&& buffer_append(&buffer, "\n")
		&& buffer_flush(&buffer))
		write(STDERR_FILENO, buffer.buf, buffer.length);
	buffer_delete(&buffer);
}
