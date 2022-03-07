/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tokenizer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 12:17:51 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/05 12:18:34 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_TOKENIZER_H
# define T_TOKENIZER_H

# include "type/t_token_list.h"
# include <stddef.h>

typedef int					(t_tokenizer_fn)(t_token_list *, char **);
typedef struct s_tokenizer	t_tokenizer;

struct s_tokenizer
{
	char const		*characters;
	size_t			length;
	t_tokenizer_fn	*fn;
};

#endif
