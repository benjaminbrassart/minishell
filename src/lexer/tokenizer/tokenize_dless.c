/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_dless.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:37:17 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 13:01:59 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "tokenizer.h"

int	tokenize_dless(t_token_list *list, char **input)
{
	int	res;

	res = lex_add_token(list, (t_token_param){D_LESS, *input, 0});
	(*input) += 2;
	return (res);
}
