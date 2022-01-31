/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:29:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 08:38:59 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef int	t_token;

enum e_token
{
	WORD_NQ = 1 << 0,
	WORD_SQ = 1 << 1,
	WORD_DQ = 1 << 2,
	WORD = WORD_NQ | WORD_SQ | WORD_SQ,
	PIPE = 1 << 3,
	LESS = 1 << 4,
	D_LESS = 1 << 5,
	GREAT = 1 << 6,
	D_GREAT = 1 << 7,
	SEPARATOR = 1 << 8,
};

#endif
