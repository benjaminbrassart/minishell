/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:23:10 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/14 11:11:36 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "executor.h"
#include "ft.h"
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
	t_exec_meta	meta;

	ft_memset(&meta, 0, sizeof (meta));
	meta.sh = sh;
	if (exec_build(&sh->tokens, &meta))
	{
		exec_run(&meta);
		exec_delete(&meta);
	}
	add_history(line);
}

static int	process_end(t_sh *sh)
{
	lex_delete(&sh->tokens);
	env_destroy(&sh->env);
	clear_history();
	write(STDERR_FILENO, EXIT_MESSAGE "\n", sizeof (EXIT_MESSAGE));
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
