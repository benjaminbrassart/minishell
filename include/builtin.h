/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:11:44 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/15 03:07:41 by bbrassar         ###   ########.fr       */
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

/* cd <path> */
int			builtin_cd(int argc, char *argv[], t_env_table *env);
/* echo [-n] [string...] */
int			builtin_echo(int argc, char *argv[], t_env_table *env);
/* pwd */
int			builtin_pwd(int argc, char *argv[], t_env_table *env);
/* export <var1=val1> [var2=val2...] */
int			builtin_export(int argc, char *argv[], t_env_table *env);
/* unset [var...] */
int			builtin_unset(int argc, char *argv[], t_env_table *env);
/* env */
int			builtin_env(int argc, char *argv[], t_env_table *env);
/* exit [code] */
int			builtin_exit(int argc, char *argv[], t_env_table *env);

/**
 * Get a builtin by its name
 *
 * @return NULL if not found
 */
t_builtin	*get_builtin(char const *name);

void		builtin_error(char const *name, char const *msg);
void		builtin_ferror(char const *name, char const *file, char const *msg);
void		builtin_aerror(char const *name, char const *arg, char const *msg);

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
