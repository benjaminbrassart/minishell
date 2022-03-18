/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:23:10 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/18 18:08:43 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "executor.h"
#include "ft.h"
#include "heredoc.h"
#include "lexer.h"
#include "minishell.h"
#include "status.h"
#include "utils.h"
#include <signal.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

int	g_exit_status;

static int	is_line_empty(char const *line)
{
	while (*line && ft_isspace(*line))
		++line;
	return (*line == 0);
}

static void	process_line(t_sh *sh)
{
	t_exec_meta	meta;

	ft_memset(&meta, 0, sizeof (meta));
	meta.sh = sh;
	if (command_count(&sh->tokens) > 0)
	{
		if (exec_build(&sh->tokens, &meta) && lex_heredoc_write(&meta))
			exec_run(&meta);
	}
	else
		exec_empty(&meta);
}

static int	process_end(t_sh *sh)
{
	lex_delete(&sh->tokens);
	env_destroy(&sh->env);
	clear_history();
	if (!sh->force_exit)
		write(STDERR_FILENO, EXIT_MESSAGE "\n", sizeof (EXIT_MESSAGE));
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (g_exit_status % EXIT_STATUS_MAX);
}

int	main(
	int argc __attribute__((unused)),
	char *argv[] __attribute__((unused)),
	char *envp[]
)
{
	t_sh	sh;
	char	*line;

	g_exit_status = 0;
	if (!setup(&sh, envp))
		return (EXIT_FAILURE);
	while (1)
	{
		if (sh.force_exit)
			break ;
		line = readline(DEFAULT_PROMPT);
		if (!line)
			break ;
		if (!is_line_empty(line))
		{
			if (lex_tokenize(&sh.tokens, line)
				&& lex_heredoc(&sh.tokens, &sh.heredoc)
				&& lex_expand(&sh.tokens, &sh.env)
				&& lex_postexpand(&sh.tokens)
				&& lex_check_syntax(&sh.tokens) && sh.tokens.length > 0)
				process_line(&sh);
			add_history(line);
			lex_delete(&sh.tokens);
			lex_heredoc_delete(&sh.heredoc);
		}
		free(line);
	}
	return (process_end(&sh));
}
