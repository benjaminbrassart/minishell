/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:36:58 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 13:02:59 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "tokenizer.h"

int	tokenize_pipe(t_token_list *list, char **input)
{
	return (lex_add_token(list, (t_token_param){PIPE, ++(*input), 0}));
}
