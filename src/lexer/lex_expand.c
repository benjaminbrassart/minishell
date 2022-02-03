/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 07:38:11 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/03 16:03:27 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

int	lex_expand(t_sh *sh)
{
	t_token_node	*node;
	char			*s;

	node = sh->tokens.first_node;
	while (node)
	{
		if (node->token & (WORD_NQ | WORD_DQ))
		{
			s = exp_expand(sh, node->value);
			if (s)
				node->value = (free(node->value), s);
			else
				return (0);
		}
		node = node->next;
	}
	return (1);
}
