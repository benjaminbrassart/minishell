/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 07:38:11 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/05 12:25:42 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

int	lex_expand(t_token_list *list, t_env *env)
{
	t_token_node	*node;
	char			*s;

	node = list->first_node;
	while (node != NULL)
	{
		if (node->token & (WORD_NQ | WORD_DQ))
		{
			s = exp_expand(env, node->value);
			if (s == NULL)
				return (0);
			free(node->value);
			node->value = s;
		}
		node = node->next;
	}
	return (1);
}
