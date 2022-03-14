/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word_dquote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:36:43 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/14 17:17:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "lexer.h"
#include "tokenizer.h"

int	tokenize_word_dquote(t_token_list *list, char **input)
{
	size_t	i;
	int		res;
	
	i = ft_strcspn(++(*input), "\"");
	res = lex_add_token(list, (t_token_param){WORD_DQ, *input, i});
	*input += i + 1;
	if (res && ft_isspace(**input))
		res = lex_add_token(list, (t_token_param){SEPARATOR, "", 0});
	return (res);
}
