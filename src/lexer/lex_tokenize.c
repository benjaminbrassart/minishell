/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:42:52 by bbrassar          #+#    #+#             */
/*   Updated: 2021/12/13 03:53:53 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

static int	add_token(t_token_list *list, t_token token, char *input,
	size_t index)
{
	t_token_node	*node;
	char			*value;

	value = NULL;
	if (index && input)
	{
		value = ft_strndup(input, index);
		if (!value)
			return (0);
	}
	node = malloc(sizeof (*node));
	if (!node)
	{
		free(value);
		return (0);
	}
	node->token = token;
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
			if (!add_token(list, WORD, input, i++))
				return (0);
		}
		else if (*input == '\"')
		{
			i = ft_strcspn(++input, "\"");
			if (!add_token(list, WORD, input, i++))
				return (0);
		}
		else if (*input == '|')
		{
			if (!add_token(list, PIPE, ++input, 0))
				return (0);
		}
		else if (*input == '>')
		{
			if (*(input + 1) == '>')
			{
				if (!add_token(list, D_GREAT, ++input, 0))
					return (0);
			}
			else if (!add_token(list, GREAT, ++input, 0))
				return (0);
		}
		else if (*input == '<')
		{
			if (*(input + 1) == '<')
			{
				if (!add_token(list, D_LESS, ++input, 0))
					return (0);
			}
			else if (!add_token(list, LESS, ++input, 0))
				return (0);
		}
		else
		{
			i = ft_strcspn(input, " \t>|<");
			if (!add_token(list, WORD, input, i))
				return (0);
		}
		input += i;
	}
	return (1);
}
