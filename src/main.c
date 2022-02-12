/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:23:10 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/12 01:20:21 by bbrassar         ###   ########.fr       */
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
			builtin->fn(0, NULL, &sh->env);
		}
		else
		{
			program = path_search(&sh->env, line);
			if (program)
				printf("program `%s'\n", program);
			free(program);
		}
	}
	lex_dump(&sh->tokens);
}

static int	process_end(t_sh *sh)
{
	lex_delete(&sh->tokens);
	env_destroy(&sh->env);
	clear_history();
	write(STDERR_FILENO, EXIT_MESSAGE "\n", sizeof EXIT_MESSAGE);
	return (g_exit_status % EXIT_STATUS_MAX);
}

int	main(
	int ac __attribute__((unused)),
	char *av[] __attribute__((unused)),
	char *ev[]
)
{
	static t_sh	sh = {{NULL, NULL, 0}, {NULL, NULL, 0}};
	char		*line;

	g_exit_status = 0;
	if (!setup(&sh, ev))
		return (EXIT_FAILURE);
	while (1)
	{
		line = readline(COMMAND_PROMPT);
		if (!line)
			break ;
		if (lex_tokenize(&sh.tokens, line) && lex_expand(&sh.tokens, &sh.env)
			&& lex_postexpand(&sh.tokens) && lex_check_syntax(&sh.tokens)
			&& sh.tokens.length > 0)
			process_line(&sh, line);
		lex_delete(&sh.tokens);
		free(line);
	}
	return (process_end(&sh));
}
