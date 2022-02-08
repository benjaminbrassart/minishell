/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:11:44 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/08 02:49:11 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "type/t_builtin.h"
# include "type/t_env.h"

# define BUILTIN_CD "cd"
# define BUILTIN_ECHO "echo"
# define BUILTIN_PWD "pwd"
# define BUILTIN_EXPORT "export"
# define BUILTIN_UNSET "unset"
# define BUILTIN_ENV "env"
# define BUILTIN_EXIT "exit"

int			builtin_cd(int argc, char *argv[], t_env_table *env);
int			builtin_echo(int argc, char *argv[], t_env_table *env);
int			builtin_pwd(int argc, char *argv[], t_env_table *env);
int			builtin_export(int argc, char *argv[], t_env_table *env);
int			builtin_unset(int argc, char *argv[], t_env_table *env);
int			builtin_env(int argc, char *argv[], t_env_table *env);
int			builtin_exit(int argc, char *argv[], t_env_table *env);

t_builtin	*get_builtin(char const *name);

void		builtin_error(char const *name, char const *msg);
void		builtin_ferror(char const *name, char const *file, char const *msg);

static t_builtin const	g_builtins[] = {
{BUILTIN_CD, builtin_cd},
{BUILTIN_ECHO, builtin_echo},
{BUILTIN_PWD, builtin_pwd},
{BUILTIN_EXPORT, builtin_export},
{BUILTIN_UNSET, builtin_unset},
{BUILTIN_ENV, builtin_env},
{BUILTIN_EXIT, builtin_exit}
};

#endif
