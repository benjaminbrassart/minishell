/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:28:08 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/03 23:22:13 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SH_H
# define T_SH_H

# include "type/t_env_table.h"
# include "type/t_heredoc.h"
# include "type/t_token_list.h"

typedef struct s_sh	t_sh;

struct s_sh
{
	char			*line;
	t_token_list	tokens;
	t_env_table		env;
	t_heredoc		heredoc;
	int				force_exit;
	int				is_interactive;
};

#endif
