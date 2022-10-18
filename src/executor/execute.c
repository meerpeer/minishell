/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:24:35 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/18 11:02:21 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	execute_builtin(t_cmd *cmd_data, t_mini *mini_data)
{
	printf("cmd->cmd[0] = %s\n", cmd_data->cmd[0]);
	if (ft_strncmp(cmd_data->cmd[0], "echo", 5) == 0)
		echo_builtin(cmd_data, mini_data);
	else if (ft_strncmp(cmd_data->cmd[0], "pwd", 4) == 0)
		pwd_builtin(mini_data);
	else if (ft_strncmp(cmd_data->cmd[0], "unset", 6) == 0)
		unset_builtin(cmd_data, mini_data);
	else if (ft_strncmp(cmd_data->cmd[0], "exit", 5) == 0)
		exit_builtin(cmd_data, mini_data);
	else if (ft_strncmp(cmd_data->cmd[0], "cd", 3) == 0)
		cd_builtin(cmd_data, mini_data);
	else if (ft_strncmp(cmd_data->cmd[0], "export", 7) == 0)
		export_builtin(cmd_data, mini_data);
	else if (ft_strncmp(cmd_data->cmd[0], "env", 4) == 0)
		env_builtin(cmd_data, mini_data);
	return ; //should return error?
}
/**
	* Child process (not built-in)
	* Calls functions to open all in and out files.
	* Calls functions to redirect input and output.
	* Closes all fds
	* Calls execve
	* @param *in_files: the first in_file of the current command;
	* @return the fd of the last file (which should be the infile used)
*/
void	child_process(t_cmd *cmd, char **envp)
{
	(void) envp;
	(void) cmd;
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
void	execute_in_child(t_cmd *cmd_data, t_mini *mini_data)
{
	int		pipe_fds[2];
	pid_t	pid;
	
	if(pipe(pipe_fds) == -1)
		error_exit(strerror(errno), 1);
	pid = fork();
	if (pid == -1)
		error_exit(strerror(errno), 1);
	if (pid == 0)
	{
		if(is_builtin(cmd_data->cmd[0]))
			execute_builtin(cmd_data, mini_data);
		else
			child_process(cmd_data, mini_data->envp);
	}
	//dup2(pipe)
	wait_for_cmd(mini_data, pid);
	return ;
}

void	execute_cmds(t_mini *data)
{
	t_cmd	*cmd_data;

	cmd_data = data->cmds;
	// save std?
	while (cmd_data)
	{
		if (data->cmd_count == 1 && is_builtin(cmd_data->cmd[0]))
		{
			execute_builtin(cmd_data, data);
			break ;
		}
		execute_in_child(cmd_data, data);
		cmd_data = cmd_data->next;
	}
	//restore stdin?
}
