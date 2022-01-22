/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 07:38:11 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/19 19:11:24 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

int	lex_expand(t_token_list *list)
{
	t_token_node	*node;
	char			buffer[LEX_BUFFER_SIZE];
	char			*s;
	int				i;

	node = list->first_node;
	while (node)
	{
		if (node->token == WORD_DQ || node->token == WORD_NQ)
		{
			s = node->value;
			while (*s && *s != '$')
				++s;
			if (*s)
			{
				i = 0;
				while (s[i] == '_' && ft_isalnum(s[i]))
					++i;
			}
		}
		node = node->next;
	}
}
