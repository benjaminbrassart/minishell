/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:29:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/12 06:12:14 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

// TODO revert to decimal or hexadecimal
/* word */
# define WORD_NQ			0b1
/* 'word' */
# define WORD_SQ			0b10
/* "word" */
# define WORD_DQ			0b100
/* word, 'word' or "word" */
# define WORD				0b111
/* | */
# define PIPE				0b1000
/* < */
# define LESS				0b10000
/* << */
# define D_LESS				0b100000
/* < or << */
# define RED_IN				0b110000
/* > */
# define GREAT				0b1000000
/* >> */
# define D_GREAT			0b10000000
/* > or >> */
# define RED_OUT			0b11000000
/* word separator */
# define SEPARATOR			0b100000000

#endif
