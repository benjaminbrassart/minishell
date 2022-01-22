/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:29:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/19 16:48:07 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token	t_token;

enum e_token
{
	WORD_NQ,
	WORD_SQ,
	WORD_DQ,
	PIPE,
	LESS,
	D_LESS,
	GREAT,
	D_GREAT,
	SEPARATOR,
};

#endif
