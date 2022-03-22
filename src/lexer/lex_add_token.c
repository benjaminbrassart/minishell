/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_add_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:54:07 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/22 04:43:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	lex_add_token(t_token_list *list, t_token_param param)
{
	t_token_node	*node;
	char			*value;

	value = NULL;
	if (param.value)
	{
		value = ft_strndup(param.value, param.index);
		if (!value)
		{
			perror(PROGRAM_NAME);
			return (0);
		}
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
	__lex_add(list, node);
	return (1);
}
