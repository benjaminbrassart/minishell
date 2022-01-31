/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_great.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:38:30 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 12:55:29 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "tokenizer.h"

int	tokenize_great(t_token_list *list, char **input)
{
	return (lex_add_token(list, (t_token_param){GREAT, ++(*input), 0}));
}
