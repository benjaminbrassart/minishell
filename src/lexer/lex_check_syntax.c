/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 05:55:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/12 02:07:59 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "lexer.h"
#include "minishell.h"
#include "status.h"
#include <stdio.h>
#include <unistd.h>

static char const	*get_token_symbol(t_token_node *node)
{
	int	token;

	if (node)
	{
		token = node->token;
		if (token == PIPE)
			return ("|");
		if (token == LESS)
			return ("<");
		if (token == D_LESS)
			return ("<<");
		if (token == GREAT)
			return (">");
		if (token == D_GREAT)
			return (">>");
	}
	return ("newline");
}

static void	print_error(t_token_node *node)
{
	t_buffer	buffer;

	g_exit_status = EXIT_STATUS_MAJOR;
	buffer_init(&buffer);
	if (buffer_append(&buffer, PROGRAM_NAME)
		&& buffer_append(&buffer, ": syntax error near unexpected token `")
		&& buffer_append(&buffer, get_token_symbol(node))
		&& buffer_append(&buffer, "'\n") && buffer_flush(&buffer))
		write(STDERR_FILENO, buffer.buf, buffer.length);
	buffer_delete(&buffer);
}

int	lex_check_syntax(t_token_list *list)
{
	t_token_node	*node;

	node = list->first_node;
	while (node)
	{
		if (node == list->first_node && (node->token == PIPE))
			return (print_error(node), 0);
		if (node == list->last_node && (node->token
			& (PIPE | LESS | D_LESS | GREAT | D_GREAT)))
			return (print_error(node->next), 0);
		if (node->token & (PIPE | LESS | D_LESS | GREAT | D_GREAT)
			&& (node->next->token & ~WORD))
			return (print_error(node->next), 0);
		node = node->next;
	}
	return (1);
}
