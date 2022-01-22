/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:28:08 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/22 07:31:05 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "type/env.h"
# include "type/token_list.h"

typedef struct s_sh	t_sh;

struct s_sh
{
	char const		*program;
	t_token_list	tokens;
	t_env			*env;
};

#endif
