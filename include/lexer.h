/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:16:15 by bbrassar          #+#    #+#             */
/*   Updated: 2021/12/13 01:15:37 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>

typedef enum e_token		t_token;
typedef struct s_token_list	t_token_list;
typedef struct s_token_node	t_token_node;

enum e_token
{
	WORD,
	PIPE,
	LESS,
	D_LESS,
	GREAT,
	D_GREAT,
};

struct s_token_list
{
	t_token_node	*first_node;
	t_token_node	*last_node;
	size_t			length;
};

struct s_token_node
{
	t_token			token;
	char			*value;
	t_token_node	*next;
};

int		lex_tokenize(t_token_list *list, char *input)
		__attribute__((nonnull(1, 2)));

void	lex_delete(t_token_list *list)
		__attribute__((nonnull(1)));

void	lex_dump(t_token_list *list)
		__attribute__((nonnull(1)));

#endif
