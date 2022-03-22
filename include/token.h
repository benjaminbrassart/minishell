/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:29:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/22 05:13:13 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/* word */
# define WORD_NQ			1
/* 'word' */
# define WORD_SQ			2
/* "word" */
# define WORD_DQ			4
/* WORD_NQ | WORD_SQ | WORD_SQ */
# define WORD				7
/* | */
# define PIPE				8
/* < */
# define LESS				16
/* << */
# define D_LESS				32
/* LESS | D_LESS */
# define RED_IN				48
/* > */
# define GREAT				64
/* >> */
# define D_GREAT			128
/* GREAT | D_GREAT */
# define RED_OUT			192
/* word separator */
# define SEPARATOR			256

#endif
