/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:24:32 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/13 10:31:45 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//open in files
//every command can have multiple in files, try to open them all WRONLY
//here_doc is also a thing here...
//exit child process on fail
int	open_infiles(t_cmd *cmd)
{
	t_file	*file;
	int		last_fd;

	last_fd = -1;
	file = cmd->in_files;
	while (file)
	{
		if (file->file_type == INPUT)
		{
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