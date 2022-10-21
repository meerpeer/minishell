/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:24:32 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/21 11:12:52 by mevan-de      ########   odam.nl         */
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
void	open_files(int *fd_to_change, t_file *file_list)
{
	t_file	*file;
	int		last_fd;

	last_fd = 0;
	file = file_list;
	while (file)
	{
		if(last_fd != 0)
			close (last_fd);
		if (file->file_type == INPUT)
			last_fd = open(file->file_name, O_RDONLY);
		else if (file->file_type == OUTPUT_APPEND)
			open(file->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (file->file_type == OUTPUT_TRUNC)
			open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (last_fd < 0)
			return (perror(file->file_name), error_exit(NULL , 1));
		*fd_to_change = last_fd;
		file = file->next;
	}
}

//redirect in files
void	redirect_in(int *fd_in, t_file *in_files)
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
void	redirect_out(int *fd_out, t_file *out_files, int pipe_write)
{
	open_files(fd_out, out_files);
	if (*fd_out > 0)
	{
		if (dup2(*fd_out, STDOUT_FILENO) == -1)
			perror("dup2");
		close(*fd_out);
	}
	else
	{
		if (dup2(pipe_write, STDOUT_FILENO) == -1)
			perror("dup2");
	}
	close(pipe_write);
}
