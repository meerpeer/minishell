/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:24:32 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/14 11:07:23 by mevan-de      ########   odam.nl         */
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
int	open_infiles(t_file *in_files)
{
	t_file	*file;
	int		last_fd;

	last_fd = 0;
	file = in_files;
	while (file)
	{
		if (file->file_type == INPUT)
		{
			if(last_fd != 0)
				close (last_fd);
			last_fd = open(file->file_name, O_RDONLY);
			if (last_fd < 0)
				error_exit(0, errno);
		}
		file = file->next;
	}
	return (last_fd);
}

int	open_outfiles(t_cmd *cmd)
{
	(void) cmd;
	return (1);
}

//open out files
//every command can have multiple out files
//exit on fail

//redirect in files
//check re
void	redirect_in(t_cmd *cmd, t_mini *data)
{
	(void) cmd;
	(void) data;
	
}

//redirect out files

//close all fds
void	close_unused_fds()
{
	return ;
}