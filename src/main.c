/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:23:10 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/22 11:47:56 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "lexer.h"
#include "minishell.h"
#include <signal.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

static void	process_line(t_sh *sh, char *line)
{
	add_history(line);
	free(line);
	lex_dump(&sh->tokens);
	lex_delete(&sh->tokens);
}

static int	process_end(t_sh *sh)
{
	lex_delete(&sh->tokens);
	rl_clear_history();
	write(STDERR_FILENO, "exit\n", 5);
	return (g_exit_status);
}

int	main(
	int ac __attribute__((unused)),
	char *av[] __attribute__((unused)),
	char *ev[]
)
{
	static t_sh	sh = {{NULL, NULL, 0}, NULL};
	char		*line;

	g_exit_status = 0;
	if (!setup(&sh, ev))
		return (EXIT_FAILURE);
	while (1)
	{
		line = readline(COMMAND_PROMPT);
		if (!line)
			break ;
		lex_tokenize(&sh.tokens, line);
		if (!sh.tokens.length)
			continue ;
		process_line(&sh, line);
	}
	return (process_end(&sh));
}
