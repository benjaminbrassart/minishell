/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_table.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 01:45:56 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/08 00:24:15 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ENV_TABLE_H
# define T_ENV_TABLE_H

# include "type/t_env.h"
# include <stddef.h>

typedef struct s_env_table	t_env_table;

struct s_env_table
{
	void	*sh;
	t_env	*first_entry;
	t_env	*last_entry;
	size_t	count;
};

#endif
