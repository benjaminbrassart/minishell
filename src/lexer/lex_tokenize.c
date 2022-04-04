/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:42:52 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 04:29:51 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>

static int	_tokenize(t_tokenizer *tokenizer, t_token_list *list, char **input,
	char *line)
{
	if (!tokenizer->fn(list, input))
	{
		perror(PROGRAM_NAME);
		return (0);
	}
	return (1);
}

int	lex_tokenize(t_token_list *list, char *input)
{
	t_tokenizer	*tokenizer;
	char		*line;

	line = ft_strtrim(input);
	free(input);
	if (line == NULL)
	{
		perror(PROGRAM_NAME);
		return (0);
	}
	input = line;
	while (*input != 0)
	{
		while (ft_isspace(*input))
			++input;
		if (!*input)
			break ;
		tokenizer = get_tokenizer(input);
		if (!_tokenize(tokenizer, list, &input, line))
			break ;
	}
	if (*input != 0)
		perror(PROGRAM_NAME);
	free(line);
	return (1);
}
