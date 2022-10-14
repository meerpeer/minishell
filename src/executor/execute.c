/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:24:35 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/14 13:40:17 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//child_process
// - open all in
// - open all out
// redirect in
// redirect out
// close all the fd boys
// execve this beauty

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