/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:23:10 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/22 13:02:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
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
	t_token const	token = sh->tokens.first_node->token;
	t_builtin const	*builtin;

	add_history(line);
	if (token == WORD_NQ || token == WORD_SQ || token == WORD_DQ)
	{
		builtin = get_builtin(sh->tokens.first_node->value);
		if (builtin)
		{
			printf("builtin `%s'\n", builtin->name);
			builtin->fn(sh->env);
		}
	}
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
