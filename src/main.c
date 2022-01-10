/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:23:10 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/07 04:12:40 by bbrassar         ###   ########.fr       */
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

	setup_signal_handlers();
	while (1)
	{
		line = readline(COMMAND_PROMPT);
		if (!line)
			break ;
		lex_tokenize(&list, line);
		if (!list.length)
			continue ;
		add_history(line);
		free(line);
		lex_dump(&list);
		lex_delete(&list);
	}
	lex_delete(&list);
	rl_clear_history();
	printf("exit\n");
	return (0);
}
