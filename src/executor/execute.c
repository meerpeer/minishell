/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:24:35 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/16 12:56:14 by mevan-de      ########   odam.nl         */
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
void	child_process(*t_cmd *cmd, char **envp)
{
	// int	in_fd;

		
	// if (execve(cmd->path, cmd->cmd, envp ) == -1)
	// {
	// 	perror(0);
	// 	exit(1);
	// }
}

/**
	* Executes executes either builtin, or non-builtin commands
	* @param *data: minishell data;
	* @return VOID
*/
void	execute_cmds(t_mini *data)
{
	t_cmd	*cmd;
	t_exec	*exec;

	exec = ft_calloc(sizeof(t_exec), 1);
	cmd = data->cmds;
	while (cmd)
	{
		// check if no pipes and builtin (you don't want to do a cd in
		// a child if no pipes as it won't work), with pipes it should
		// be done in the child
		if(pipe(exec->pipe_fd) == -1)
			error_exit(strerror(errno), 1);
		exec->pid = fork();
		if (exec->pid == -1)
			error_exit(strerror(errno), 1);
		if (exec->pid == 0)
		{
			//if(is_builtin(cmd->cmd[0]))
			//		do builtins
			//else
			child_process(cmd, data->envp);
		}
		wait_for_cmd(data, exec->pid);
		cmd = cmd->next;
	}
	free(exec);
}
