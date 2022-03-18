/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word_squote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:36:33 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/18 17:43:59 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "lexer.h"
#include "tokenizer.h"

int	tokenize_word_squote(t_token_list *list, char **input)
{
	size_t	i;
	int		res;

	i = ft_strcspn(++(*input), "\'");
	res = lex_add_token(list, (t_token_param){WORD_SQ, *input, i});
	*input += (i + 1);
	if (res && ft_isspace(**input))
		res = lex_add_token(list, (t_token_param){SEPARATOR, NULL, 0});
	return (res);
}
