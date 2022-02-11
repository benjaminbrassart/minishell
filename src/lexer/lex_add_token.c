/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_add_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:54:07 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/11 05:00:48 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "lexer.h"
#include <stdlib.h>

int	lex_add_token(t_token_list *list, t_token_param param)
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
	__lex_add(list, node);
	return (1);
}
