/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:16:15 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/18 17:43:11 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "type/t_sh.h"
# include "type/t_token_list.h"

/**
 * add NODE to LIST
 */
void	__lex_add(t_token_list *list, t_token_node *node)
		__attribute__((nonnull(1, 2)));

/**
 * break INPUT into tokens, and add them to LIST
 */
int		lex_tokenize(t_token_list *list, char *input)
		__attribute__((nonnull(1, 2)));

/**
 * free all nodes in LIST
 */
void	lex_delete(t_token_list *list)
		__attribute__((nonnull(1)));

/**
 * add a node deduced from PARAM to LIST
 */
int		lex_add_token(t_token_list *list, t_token_param param)
		__attribute__((nonnull(1)));

/**
 * check if the order of the elements of LIST is a correct shell syntax
 */
int		lex_check_syntax(t_token_list *list);

/**
 * expand variables in the elements of LIST from ENV
 * example: `$TERM' becomes `xterm-256color'
 */
int		lex_expand(t_token_list *list, t_env_table *env);

int		lex_concat(t_token_list *list);

int		lex_postexpand(t_token_list *list);

#endif
