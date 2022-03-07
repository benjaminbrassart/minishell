/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word_nquote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:36:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 12:59:06 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "lexer.h"
#include "tokenizer.h"

int	tokenize_word_nquote(t_token_list *list, char **input)
{
	size_t	i;
	int		res;

	i = ft_strcspn(*input, " \t>|<'\"");
	res = lex_add_token(list, (t_token_param){WORD_NQ, *input, i});
	*input += i;
	if (res && ft_isspace(**input))
		res = lex_add_token(list, (t_token_param){SEPARATOR, "", 0});
	return (res);
}
