/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_builtin.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 12:04:14 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 01:48:47 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_BUILTIN_H
# define T_BUILTIN_H

# include "type/t_env_table.h"

typedef int	(*t_builtin_fn)(int, char *[], t_env_table *);
typedef struct s_builtin
{
	char const		*name;
	t_builtin_fn	fn;
}	t_builtin;

#endif
