/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 04:48:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/03/14 18:55:21 by msainton         ###   ########.fr       */
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

int		exec_empty(t_token_list *list);

void	exec_delete(t_exec_meta *meta);

#endif
