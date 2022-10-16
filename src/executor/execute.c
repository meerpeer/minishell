/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:24:35 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/16 10:19:40 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
	* Child process (not built-in)
	* Calls functions to open all in and out files.
	* Calls functions to redirect input and output.
	* Closes all fds
	* Calls execve
	* @param *in_files: the first in_file of the current command;
	* @return the fd of the last file (which should be the infile used)
*/
void	child_process(/*t_cmd *cmd, char **envp*/)
{
	// int	in_fd;

		
	// if (execve(cmd->path, cmd->cmd, envp ) == -1)
	// {
	// 	perror(0);
	// 	exit(1);
	// }
}

//execute
//check if build in
//pipe and fork :)
//if( child)
//	child_process
//if (parent)
//	close pipe ends?
//	don't close STDIN/ STDOUT
/**
	* Executes commands. First checks if it's a builtin or not
	* Calls functions to open all in and out files.
	* Calls functions to redirect input and output.
	* Closes all fds
	* Calls execve
	* @param *in_files: the first in_file of the current command;
	* @return the fd of the last file (which should be the infile used)
*/
void	execute_cmd(t_mini *data)
{
	t_cmd *cmd;

	cmd = data->cmds;
	while (cmd)
	{
		//is builtin?
		cmd = cmd->next;
	}
}