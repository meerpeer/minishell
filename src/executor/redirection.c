/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merel <merel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:24:32 by mevan-de          #+#    #+#             */
/*   Updated: 2022/11/03 12:46:44 by merel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
	* Function that opens all the in files and exits if one of them fails. 
	* Every command can have multiple in files, try to open them all RDONLY.
	* Closes all unused fds. 
	* TODO: Here_doc is also a thing here.
	* @param *in_files: the first in_file of the current command;
	* @return the fd of the last file (which should be the infile used)
*/
void	open_files(int *fd_to_change, t_list *file_list)
{
	t_file	*file;
	int		last_fd;

	last_fd = 0;
	while (file_list)
	{
		file = file_list->content;
		if(last_fd != 0)
			close (last_fd);
		if (file->file_type == INPUT)
			last_fd = open(file->file_name, O_RDONLY);
		else if (file->file_type == OUTPUT_APPEND)
			last_fd = open(file->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (file->file_type == OUTPUT_TRUNC)
			last_fd = open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (last_fd < 0)
			return (perror(file->file_name), error_exit(NULL , 1));
		*fd_to_change = last_fd;
		file_list = file_list->next;
	}
}

//redirect in files
void	redirect_in(int *fd_in, t_list *in_files)
{
	open_files(fd_in, in_files);
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
	open_files(&cmd->fd_out, cmd->out_files);
	if (cmd->fd_out > 0)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("dup2");
		close(cmd->fd_out);
	}
	else
	{
		if (dup2(cmd->pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
			perror("dup2");
		if (cmd->cmd_index == mini_data->cmd_count - 1)
		{
			if (dup2(mini_data->std_backup[WRITE_END], STDOUT_FILENO) == -1)
				perror("dup2");
		}
	}
	close(cmd->pipe_fd[WRITE_END]);
}
