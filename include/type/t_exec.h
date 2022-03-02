/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 02:29:20 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/02 14:26:21 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_EXEC_H
# define T_EXEC_H

# include "type/t_builtin.h"
# include "type/t_sh.h"
# include <stddef.h>

typedef struct s_exec_meta	t_exec_meta;
typedef struct s_exec		t_exec;

union u_exec_interface
{
	char			*path;
	t_builtin_fn	builtin;
};

struct s_exec_meta
{
	t_sh	*sh;
	size_t	count;
	t_exec	*exec;
};

struct s_exec
{
	t_exec_meta				*meta;
	union u_exec_interface	interface;
	size_t					argc;
	char					**argv;
	int						is_builtin;
	int						fd_in;
	int						fd_out;
	int						fd_save;
	int						search_path;
};

#endif
