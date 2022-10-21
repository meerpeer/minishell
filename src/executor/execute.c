/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:24:35 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/21 11:11:02 by mevan-de      ########   odam.nl         */
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
void	child_process(t_cmd *cmd, char **env, int pipe_fds[2])
{
	(void) env;
	
	redirect_in(&cmd->fd_in, cmd->in_files);
	redirect_out(&cmd->fd_out, cmd->out_files, pipe_fds[WRITE_END]);
	//get cmd path
	if (execve(cmd->cmd_path, cmd->cmd, env) == -1)
	{
		perror("minishell :");
		exit (1);
	}
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
	mini_data->last_pid = pid;
	if (pid == -1)
		perror("fork:");
	if (pid == 0)
	{
		if(is_builtin(cmd_data->cmd[0]))
			execute_builtin(cmd_data, mini_data);
		else
			child_process(cmd_data, mini_data->env, pipe_fds);
	}
	close (pipe_fds[WRITE_END]);
	save_read_fd(cmd_data, pipe_fds[READ_END]);
	close (pipe_fds[READ_END]);
	return ;
}

void	execute_cmds(t_mini *data)
{
	t_cmd	*cmd_data;

	cmd_data = data->cmds;
	data->last_pid = -1;
	backup_std_in_and_out(data->std_backup);
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
	wait_for_cmds(&data->exit_status, data->last_pid);
	restore_std_in_and_out(data->std_backup);
}
