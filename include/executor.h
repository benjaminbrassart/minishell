/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 04:48:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/21 23:00:11 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define REDIRECTION_UMASK 0644
# define MESSAGE_CHILD_QUIT "Quit"
# define MESSAGE_CHILD_SEGV "Segmentation fault"
# define MESSAGE_COMMAND_NF "Command not found"
# define MESSAGE_EXEC_DIR "Is a directory"

# include "type/t_exec.h"

int		exec_build(t_token_list *list, t_exec_meta *meta_p);

int		exec_build_redirect(t_exec_meta *meta);

int		exec_pipe(t_exec_meta *meta);

int		exec_redirect(t_exec *exec);

int		exec_run(t_exec_meta *meta);

int		exec_empty(t_exec_meta *meta);

void	exec_delete(t_exec_meta *meta);

void	exec_delete_redirect(t_exec_meta *meta);

#endif
