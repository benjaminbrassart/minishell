/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_exec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 02:29:20 by bbrassar          #+#    #+#             */
/*   Updated: 2022/04/04 04:59:18 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_EXEC_H
# define T_EXEC_H

# include "type/t_builtin.h"
# include "type/t_sh.h"
# include <stddef.h>

typedef struct s_exec_meta	t_exec_meta;
typedef struct s_exec		t_exec;
typedef struct s_exec_red	t_exec_red;

union u_exec_interface
{
	char			*path;
	t_builtin_fn	builtin;
};

struct s_exec_red
{
	char				*path;
	int					type;
	int					fd;
	t_heredoc_buffer	*hd;
	t_exec				*exec;
	t_exec_red			*next;
};

struct s_exec_meta
{
	t_sh	*sh;
	t_exec	*exec;
	size_t	count;
	size_t	started;
};

struct s_exec
{
	t_exec_meta				*meta;
	union u_exec_interface	interface;
	size_t					argc;
	size_t					index;
	char					**argv;
	int						is_builtin;
	int						search_path;
	int						fds[2];
	int						fd_in;
	int						fd_out;
	t_exec_red				*red;
};

#endif
