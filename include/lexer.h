/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:16:15 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/03 21:18:35 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "type/sh.h"
# include "type/token_list.h"

# define LEX_BUFFER_SIZE 4096
# define LEX_SYNTAX_ERRNUM 127

int		lex_tokenize(t_token_list *list, char *input)
		__attribute__((nonnull(1, 2)));

void	lex_delete(t_token_list *list)
		__attribute__((nonnull(1)));

void	lex_dump(t_token_list *list)
		__attribute__((nonnull(1)));

int		lex_add_token(t_token_list *list, t_token_param param)
		__attribute__((nonnull(1)));

int		lex_expand(t_sh *sh);

int		lex_postexpand(t_sh *sh);

#endif
