/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:23:10 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/05 12:25:30 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "lexer.h"
#include "minishell.h"
#include "status.h"
#include <signal.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

static void	process_line(t_sh *sh, char *line)
{
	t_builtin	*builtin;
	char		*program;

	add_history(line);
	if (sh->tokens.first_node->token & WORD)
	{
		builtin = get_builtin(sh->tokens.first_node->value);
		if (builtin)
		{
			printf("builtin `%s'\n", builtin->name);
			builtin->fn(sh->env);
		}
		else
		{
			program = path_search(sh->env, line);
			if (program)
				printf("program `%s'\n", program);
		}
	}
	free(line);
	lex_dump(&sh->tokens);
	lex_delete(&sh->tokens);
}

static int	process_end(t_sh *sh)
{
	lex_delete(&sh->tokens);
	clear_history();
	write(STDERR_FILENO, EXIT_MESSAGE "\n", sizeof EXIT_MESSAGE);
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
		lex_expand(&sh.tokens, sh.env);
		lex_postexpand(&sh.tokens);
		if (!sh.tokens.length)
			continue ;
		process_line(&sh, line);
	}
	return (process_end(&sh));
}
