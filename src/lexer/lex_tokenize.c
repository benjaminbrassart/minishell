/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:42:52 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 09:58:11 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

int	lex_tokenize(t_token_list *list, char *input)
{
	size_t	i;

	while (*input)
	{
		i = 0;
		while (*input == ' ' || *input == '\t')
			++input;
		if (*input == '\'')
		{
			i = ft_strcspn(++input, "\'");
			if (!lex_add_token(list, (t_token_param){WORD_SQ, input, i++}))
				return (0);
		}
		else if (*input == '\"')
		{
			i = ft_strcspn(++input, "\"");
			if (!lex_add_token(list, (t_token_param){WORD_DQ, input, i++}))
				return (0);
		}
		else if (*input == '|')
		{
			if (!lex_add_token(list, (t_token_param){PIPE, ++input, 0}))
				return (0);
		}
		else if (*input == '>')
		{
			if (*++input == '>')
			{
				if (!lex_add_token(list, (t_token_param){D_GREAT, ++input, 0}))
					return (0);
			}
			else if (!lex_add_token(list, (t_token_param){GREAT, input, 0}))
				return (0);
		}
		else if (*input == '<')
		{
			if (*++input == '<')
			{
				if (!lex_add_token(list, (t_token_param){D_LESS, ++input, 0}))
					return (0);
			}
			else if (!lex_add_token(list, (t_token_param){LESS, input, 0}))
				return (0);
		}
		else if (*input)
		{
			i = ft_strcspn(input, " \t>|<'\"");
			if (!lex_add_token(list, (t_token_param){WORD_NQ, input, i}))
				return (0);
		}
		input += i;
		if ((*input == ' ' || *input == '\t')
			&& !lex_add_token(list, (t_token_param){SEPARATOR, "", 0}))
			return (0);
	}
	return (1);
}
