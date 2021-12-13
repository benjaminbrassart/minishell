/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:23:10 by bbrassar          #+#    #+#             */
/*   Updated: 2021/12/13 03:00:59 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

static void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

int	main(void)
{
	static t_token_list	list = {NULL, NULL, 0};
	char				*line;
	char				*prompt;

	setup_signal_handlers();
	prompt = COMMAND_PROMPT;
	while (1)
	{
		line = readline(prompt);
		prompt = COMMAND_PROMPT;
		if (!line)
			break ;
		lex_tokenize(&list, line);
		if (!list.length)
			continue ;
		if (list.last_node->token == PIPE)
		{
			prompt = PIPE_PROMPT;
			continue ;
		}
		add_history(line);
		free(line);
		lex_dump(&list);
		lex_delete(&list);
	}
	lex_delete(&list);
	rl_clear_history();
	return (0);
}
