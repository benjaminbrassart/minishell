/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:23:10 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 04:27:23 by bbrassar         ###   ########.fr       */
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

static void	process_line(t_sh *sh)
{
	t_exec_meta	meta;

	if (sh->is_interactive)
		add_history(sh->line);
	if (lex_tokenize(&sh->tokens, sh->line)
		&& lex_heredoc(&sh->tokens, &sh->heredoc)
		&& lex_expand(&sh->tokens, &sh->env)
		&& lex_postexpand(&sh->tokens)
		&& lex_check_syntax(&sh->tokens) && sh->tokens.length > 0)
	{
		ft_memset(&meta, 0, sizeof (meta));
		meta.sh = sh;
		if (!exec_build(&sh->tokens, &meta))
		{
			g_exit_status = EXIT_STATUS_MINOR;
			return ;
		}
		exec_run(&meta);
	}
}

static int	process_end(t_sh *sh)
{
	lex_delete(&sh->tokens);
	env_destroy(&sh->env);
	clear_history();
	if (sh->is_interactive)
		write(STDERR_FILENO, EXIT_MESSAGE "\n", sizeof (EXIT_MESSAGE));
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (g_exit_status % EXIT_STATUS_MAX);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_sh	sh;
	int		n;

	((void)argc, (void)argv);
	g_exit_status = 0;
	if (!setup(&sh, envp))
		return (EXIT_FAILURE);
	while (!sh.force_exit)
	{
		sh.line = get_line(&sh, DEFAULT_PROMPT);
		if (sh.line == NULL)
			break ;
		n = 0;
		while (ft_isspace(sh.line[n]))
			++n;
		if (sh.line[n] == 0)
			continue ;
		process_line(&sh);
		lex_delete(&sh.tokens);
		lex_heredoc_delete(&sh.heredoc);
	}
	return (process_end(&sh));
}
