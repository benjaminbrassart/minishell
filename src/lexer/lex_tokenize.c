/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:42:52 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 13:03:37 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include "tokenizer.h"
#include <stdlib.h>

int	lex_tokenize(t_token_list *list, char *input)
{
	t_tokenizer	*tokenizer;

	while (*input)
	{
		while (ft_isspace(*input))
			++input;
		if (!*input)
			break ;
		tokenizer = get_tokenizer(input);
		if (!tokenizer->fn(list, &input))
			return (0);
	}
	return (1);
}
