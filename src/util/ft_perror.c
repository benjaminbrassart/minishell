/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:25:27 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/15 13:26:26 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "minishell.h"
#include <unistd.h>

void	ft_perror(char const *name, char const *msg)
{
	t_buffer	buffer;

	buffer_init(&buffer);
	if (buffer_append(&buffer, PROGRAM_NAME ": ")
		&& (name == NULL || (buffer_append(&buffer, name)
				&& buffer_append(&buffer, ": ")))
		&& buffer_append(&buffer, msg)
		&& buffer_append(&buffer, "\n")
		&& buffer_flush(&buffer))
		write(STDERR_FILENO, buffer.buf, buffer.length);
	buffer_delete(&buffer);
}

void	ft_paerror(char const *name, char const *arg, char const *msg)
{
	t_buffer	buffer;

	buffer_init(&buffer);
	if (buffer_append(&buffer, PROGRAM_NAME ": ")
		&& (name == NULL || (buffer_append(&buffer, name)
				&& buffer_append(&buffer, ": ")))
		&& buffer_append(&buffer, "`")
		&& buffer_append(&buffer, arg)
		&& buffer_append(&buffer, "': ")
		&& buffer_append(&buffer, msg)
		&& buffer_append(&buffer, "\n")
		&& buffer_flush(&buffer))
		write(STDERR_FILENO, buffer.buf, buffer.length);
	buffer_delete(&buffer);
}

void	ft_pferror(char const *name, char const *file, char const *msg)
{
	t_buffer	buffer;

	buffer_init(&buffer);
	if (buffer_append(&buffer, PROGRAM_NAME ": ")
		&& (name == NULL || (buffer_append(&buffer, name)
				&& buffer_append(&buffer, ": ")))
		&& buffer_append(&buffer, file)
		&& buffer_append(&buffer, ": ")
		&& buffer_append(&buffer, msg)
		&& buffer_append(&buffer, "\n")
		&& buffer_flush(&buffer))
		write(STDERR_FILENO, buffer.buf, buffer.length);
	buffer_delete(&buffer);
}
