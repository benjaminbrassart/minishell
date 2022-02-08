/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:29:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 03:54:07 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/* word */
# define WORD_NQ	1
/* 'word' */
# define WORD_SQ	2
/* "word" */
# define WORD_DQ	4
/* word, 'word' or "word" */
# define WORD		7
/* | */
# define PIPE		8
/* < */
# define LESS		16
/* << */
# define D_LESS		32
/* > */
# define GREAT		64
/* >> */
# define D_GREAT	128
/* word separator */
# define SEPARATOR	256

#endif
