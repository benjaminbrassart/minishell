/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:40:12 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 11:45:12 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "tokenizer.h"

t_tokenizer	*get_tokenizer(char *input)
{
	size_t		n;

	n = 0;
	while (g_tokenizer[n].characters && ft_strncmp(input,
			g_tokenizer[n].characters, g_tokenizer[n].length) != 0)
		++n;
	return (&g_tokenizer[n]);
}
