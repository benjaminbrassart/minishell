/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 07:38:11 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/02 17:31:34 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "env.h"
#include "lexer.h"
#include "minishell.h"
#include "status.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int	lex_expand(t_token_list *list, t_env_table *env)
{
	t_token_node	*prev;
	t_token_node	*node;
	char			*s;

	prev = NULL;
	node = list->first_node;
	while (node != NULL)
	{
		if ((prev == NULL || (prev->token & ~D_LESS))
			&& node->token & (WORD_NQ | WORD_DQ))
		{
			s = str_expand(env, node->value);
			if (s == NULL)
				return (0);
			free(node->value);
			node->value = s;
		}
		prev = node;
		node = node->next;
	}
	return (1);
}
