/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:21:24 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/21 05:11:55 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "ft.h"
#include "minishell.h"

static t_env	*from_entry(char const *s)
{
	t_env	*ent;
	char	*key;
	char	*value;
	size_t	n;

	n = 0;
	while (s[n] && s[n] != '=')
		++n;
	key = ft_strndup(s, n);
	value = ft_strdup(s + n + 1);
	ent = env_newent(key, value);
	return (ent);
}

static void	env_addent(t_sh *sh, t_env *slow, t_env *ent)
{
	if (slow)
		slow->next = ent;
	else
		sh->env = ent;
}

int	env_init(t_sh *sh, char *ev[])
{
	char	*ent;
	t_env	*slow;
	t_env	*env;

	env = sh->env;
	slow = NULL;
	ent = *ev;
	while (ent)
	{
		env = from_entry(ent);
		if (!ent)
		{
			env_destroy(sh);
			return (0);
		}
		env_addent(sh, slow, env);
		++ent;
	}
	return (1);
}
