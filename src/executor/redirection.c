/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:24:32 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/11 15:35:53 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_fd(int *fd, int new_fd)
{
	if (*fd > 0)
		close (*fd);
	*fd = new_fd;
}

/**
	* Function that opens all the in files and exits if one of them fails. 
	* Every command can have multiple in files, try to open them all RDONLY.
	* Closes all unused fds. 
	* TODO: Here_doc is also a thing here.
	* @param *in_files: the first in_file of the current command;
	* @return the fd of the last file (which should be the infile used)
*/
void	open_files(int *fd_out, int *fd_in, t_list *file_list)
{
	t_file	*file;
	int		new_fd_out;
	int		new_fd_in;

	new_fd_out = 0;
	new_fd_in = 0;
	while (file_list)
	{
		file = file_list->content;
		if (file->file_type == INPUT || file->file_type == INPUT_HEREDOC)
		{
			new_fd_in = open(file->file_name, O_RDONLY);
			update_fd(fd_in, new_fd_in);
		}
		else
		{
			if (file->file_type == OUTPUT_APPEND)
				new_fd_out = open(file->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
			else if (file->file_type == OUTPUT_TRUNC)
				new_fd_out = open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			update_fd(fd_out, new_fd_out);
		}
		if (new_fd_out < 0 || new_fd_in < 0)
			return (error_exit(file->file_name, ": ", strerror(errno), 1));
		file_list = file_list->next;
	}
}

//redirect in files
static void	redirect_in(int *fd_in)
{
	//open_files(fd_in, in_files);
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
	//open_files(&cmd->fd_out, cmd->out_files);
	if (cmd->cmd_index != mini_data->cmd_count - 1)
	{
		if (dup2(cmd->pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	close(cmd->pipe_fd[WRITE_END]);
	if (cmd->fd_out > 0)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("dup2");
		close(cmd->fd_out);
	}
}

void	redirect(t_cmd *cmd, t_mini	*mini_data)
{
	open_files(&cmd->fd_out, &cmd->fd_in, cmd->files);
	redirect_in(&cmd->fd_in);
	redirect_out(cmd, mini_data);
}
