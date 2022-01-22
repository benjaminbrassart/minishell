/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:42:52 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/21 05:56:00 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

static int	add_token(t_token_list *list, t_token_param param)
{
	t_token_node	*node;
	char			*value;

	value = NULL;
	if (param.index && param.value)
	{
		value = ft_strndup(param.value, param.index);
		if (!value)
			return (0);
	}
	node = malloc(sizeof (*node));
	if (!node)
	{
		free(value);
		return (0);
	}
	node->token = param.token;
	node->value = value;
	node->next = NULL;
	if (list->length == 0)
		list->first_node = node;
	else
		list->last_node->next = node;
	list->last_node = node;
	++list->length;
	return (1);
}

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
			if (!add_token(list, (t_token_param){WORD_SQ, input, i++}))
				return (0);
		}
		else if (*input == '\"')
		{
			i = ft_strcspn(++input, "\"");
			if (!add_token(list, (t_token_param){WORD_DQ, input, i++}))
				return (0);
		}
		else if (*input == '|')
		{
			if (!add_token(list, (t_token_param){PIPE, ++input, 0}))
				return (0);
		}
		else if (*input == '>')
		{
			if (*++input == '>')
			{
				if (!add_token(list, (t_token_param){D_GREAT, ++input, 0}))
					return (0);
			}
			else if (!add_token(list, (t_token_param){GREAT, input, 0}))
				return (0);
		}
		else if (*input == '<')
		{
			if (*++input == '<')
			{
				if (!add_token(list, (t_token_param){D_LESS, ++input, 0}))
					return (0);
			}
			else if (!add_token(list, (t_token_param){LESS, input, 0}))
				return (0);
		}
		else if (*input)
		{
			i = ft_strcspn(input, " \t>|<'\"");
			if (!add_token(list, (t_token_param){WORD_NQ, input, i}))
				return (0);
		}
		input += i;
		if ((*input == ' ' || *input == '\t')
			&& !add_token(list, (t_token_param){SEPARATOR, "", 0}))
			return (0);
	}
	return (1);
}
