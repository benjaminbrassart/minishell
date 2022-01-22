/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:11:44 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/21 05:16:55 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef int				(*t_builtin_fn)(void const *);
typedef struct s_builtin
{
	char const			*name;
	t_builtin_fn const	fn;
}	t_builtin;

int			builtin_cd(void const *a);
int			builtin_echo(void const *a);
int			builtin_pwd(void const *a);
int			builtin_export(void const *a);
int			builtin_unset(void const *a);
int			builtin_env(void const *a);
int			builtin_exit(void const *a);

t_builtin	*get_builtin(char const *name);

static t_builtin const	g_builtins[] = {
{.name = "cd", .fn = builtin_cd},
{.name = "echo", .fn = builtin_echo},
{.name = "pwd", .fn = builtin_pwd},
{.name = "export", .fn = builtin_export},
{.name = "unset", .fn = builtin_unset},
{.name = "env", .fn = builtin_env},
{.name = "exit", .fn = builtin_exit}
};

#endif
