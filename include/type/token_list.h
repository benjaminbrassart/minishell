/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:30:11 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/01 09:32:07 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include "type/token.h"
# include <stddef.h>

typedef struct s_token_list		t_token_list;
typedef struct s_token_node		t_token_node;
typedef struct s_token_param	t_token_param;

struct s_token_list
{
	t_token_node	*first_node;
	t_token_node	*last_node;
	size_t			length;
};

struct s_token_node
{
	int				token;
	char			*value;
	t_token_node	*next;
};

struct s_token_param
{
	int		token;
	char	*value;
	size_t	index;
};

#endif
