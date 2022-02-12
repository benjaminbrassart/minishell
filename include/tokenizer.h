/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:08:03 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/12 02:10:42 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "type/t_token_list.h"
# include "type/t_tokenizer.h"

int				tokenize_word_nquote(t_token_list *list, char **input);
int				tokenize_word_squote(t_token_list *list, char **input);
int				tokenize_word_dquote(t_token_list *list, char **input);
int				tokenize_pipe(t_token_list *list, char **input);
int				tokenize_dless(t_token_list *list, char **input);
int				tokenize_less(t_token_list *list, char **input);
int				tokenize_dgreat(t_token_list *list, char **input);
int				tokenize_great(t_token_list *list, char **input);

t_tokenizer		*get_tokenizer(char *input);

static t_tokenizer const	g_tokenizer[] = {
{"\'", 1, tokenize_word_squote},
{"\"", 1, tokenize_word_dquote},
{"|", 1, tokenize_pipe},
{">>", 2, tokenize_dgreat},
{">", 1, tokenize_great},
{"<<", 2, tokenize_dless},
{"<", 1, tokenize_less},
{NULL, 0, tokenize_word_nquote},
};

#endif
