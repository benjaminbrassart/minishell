/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 04:25:50 by bbrassar          #+#    #+#             */
/*   Updated: 2022/01/07 04:30:58 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_command_list	t_command_list;
typedef struct s_command_node	t_command_node;

struct s_command_list
{
	t_command_node	*first;
	unsigned int	length;
};

struct s_command_node
{
	char	*ex_name;
	char	**args;
};

#endif
