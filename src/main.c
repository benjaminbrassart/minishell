/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:23:10 by bbrassar          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/29 11:21:29 by bbrassar         ###   ########.fr       */
=======
/*   Updated: 2022/04/02 14:17:56 by bbrassar         ###   ########.fr       */
>>>>>>> bb482b249a862788f06c770ce4cf0d9658a78275
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

static char	*get_line(t_sh *sh)
{
	char	*line;
	int		res;

	if (sh->is_interactive)
		return (readline(DEFAULT_PROMPT));
	res = get_next_line(STDIN_FILENO, &line);
<<<<<<< HEAD
	if (res == 1)
		return (line);
	if (res == -1)
		perror(PROGRAM_NAME);
	return (NULL);
=======
	if (res < 0 || (res == 0 && *line == 0))
	{
		if (res == 0)
			free(line);
		else
			perror(PROGRAM_NAME);
		return (NULL);
	}
	return (line);
>>>>>>> bb482b249a862788f06c770ce4cf0d9658a78275
}

static void	process_line(t_sh *sh)
{
	t_exec_meta	meta;

	ft_memset(&meta, 0, sizeof (meta));
	meta.sh = sh;
	if (exec_build(&sh->tokens, &meta))
		exec_run(&meta);
}

static void	post_process_line(t_sh *sh, char *line)
{
	if (sh->is_interactive)
		add_history(line);
	lex_delete(&sh->tokens);
	lex_heredoc_delete(&sh->heredoc);
	free(line);
}

static int	process_end(t_sh *sh)
{
	lex_delete(&sh->tokens);
	env_destroy(&sh->env);
<<<<<<< HEAD
	if (sh->is_interactive)
	{
		clear_history();
		write(STDERR_FILENO, EXIT_MESSAGE "\n", sizeof (EXIT_MESSAGE));
	}
=======
	clear_history();
	if (sh->is_interactive)
		write(STDERR_FILENO, EXIT_MESSAGE "\n", sizeof (EXIT_MESSAGE));
>>>>>>> bb482b249a862788f06c770ce4cf0d9658a78275
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
	int		n;

	g_exit_status = 0;
	if (!setup(&sh, envp))
		return (EXIT_FAILURE);
	while (!sh.force_exit)
	{
		line = get_line(&sh);
		if (line == NULL)
			break ;
		n = 0;
		while (ft_isspace(line[n]))
			++n;
		if (line[n] == 0)
			continue ;
		if (lex_tokenize(&sh.tokens, line)
			&& lex_heredoc(&sh.tokens, &sh.heredoc)
			&& lex_expand(&sh.tokens, &sh.env) && lex_postexpand(&sh.tokens)
			&& lex_check_syntax(&sh.tokens) && sh.tokens.length > 0)
			process_line(&sh);
		post_process_line(&sh, line);
	}
	return (process_end(&sh));
}
