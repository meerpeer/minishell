/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_filehandler.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 13:48:58 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/14 14:00:32 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_fd(int *fd, int new_fd)
{
	if (*fd > 0)
		close (*fd);
	*fd = new_fd;
}

void	open_file(int *fd_out, int *fd_in, t_list *file_list)
{
	t_file	*file;
	int		new_fd;

	file = file_list->content;
	new_fd = 0;
	if (file->file_type == INPUT || file->file_type == INPUT_HEREDOC)
	{
		new_fd = open(file->file_name, O_RDONLY);
		update_fd(fd_in, new_fd);
	}
	else
	{
		if (file->file_type == OUTPUT_APPEND)
			new_fd = open(file->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (file->file_type == OUTPUT_TRUNC)
			new_fd = open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		update_fd(fd_out, new_fd);
	}
	if (new_fd < 0)
		return (error_exit(file->file_name, ": ", strerror(errno), 1));
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
	while (file_list)
	{
		open_file(fd_out, fd_in, file_list);
		file_list = file_list->next;
	}
}
