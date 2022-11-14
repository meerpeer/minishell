/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_redirection.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:24:32 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/14 14:04:44 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//redirect in files
static void	redirect_in(int *fd_in)
{
	if (*fd_in)
	{
		if (dup2(*fd_in, STDIN_FILENO) == -1)
			perror("dup2");
		close(*fd_in);
	}
}

//redirect out files
void	redirect_out(t_cmd *cmd, t_mini *mini_data)
{
	if (cmd->cmd_index != mini_data->cmd_count - 1)
	{
		if (dup2(cmd->pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
			print_error("dup2: ", strerror(errno), NULL);
	}
	close(cmd->pipe_fd[WRITE_END]);
	if (cmd->fd_out > 0)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			print_error("dup2: ", strerror(errno), NULL);
		close(cmd->fd_out);
	}
}

void	redirect(t_cmd *cmd, t_mini	*mini_data)
{
	open_files(&cmd->fd_out, &cmd->fd_in, cmd->files);
	redirect_in(&cmd->fd_in);
	redirect_out(cmd, mini_data);
}
