/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:11:44 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/31 04:43:45 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "type/env.h"

typedef int				(*t_builtin_fn)(t_env *);
typedef struct s_builtin
{
	char const		*name;
	t_builtin_fn	fn;
}	t_builtin;

int				builtin_cd(t_env *env);
int				builtin_echo(t_env *env);
int				builtin_pwd(t_env *env);
int				builtin_export(t_env *env);
int				builtin_unset(t_env *env);
int				builtin_env(t_env *env);
int				builtin_exit(t_env *env);

t_builtin		*get_builtin(char const *name);

static t_builtin const	g_builtins[] = {
{"cd", builtin_cd},
{"echo", builtin_echo},
{"pwd", builtin_pwd},
{"export", builtin_export},
{"unset", builtin_unset},
{"env", builtin_env},
{"exit", builtin_exit}
};

#endif
