/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 04:48:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/02/14 10:15:52 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "type/t_exec.h"

int		exec_build(t_token_list *list, t_exec_meta *meta_p);

int		exec_run(t_exec_meta *meta);

void	exec_delete(t_exec_meta *meta);

#endif
