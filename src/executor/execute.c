/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:24:35 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/14 13:40:07 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	execute_builtin(t_cmd *cmd_data, t_mini *mini_data)
{
	redirect(cmd_data, mini_data);
	if (ft_strncmp(cmd_data->cmd[0], "echo", 5) == 0)
		echo_builtin(cmd_data);
	else if (ft_strncmp(cmd_data->cmd[0], "pwd", 4) == 0)
		pwd_builtin(mini_data);
	else if (ft_strncmp(cmd_data->cmd[0], "unset", 6) == 0)
		unset_builtin(cmd_data, mini_data);
	else if (ft_strncmp(cmd_data->cmd[0], "exit", 5) == 0)
		exit_builtin(cmd_data->cmd, mini_data);
	else if (ft_strncmp(cmd_data->cmd[0], "cd", 3) == 0)
		cd_builtin(cmd_data, mini_data);
	else if (ft_strncmp(cmd_data->cmd[0], "export", 7) == 0)
		export_builtin(cmd_data, mini_data);
	else if (ft_strncmp(cmd_data->cmd[0], "env", 4) == 0)
		env_builtin(mini_data);
	mini_data->exit_status = 0;
	return ;
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
void	child_process(t_cmd *cmd, t_mini *mini_data)
{
	extern char	**environ;
	
	close(cmd->pipe_fd[READ_END]);
	redirect(cmd, mini_data);
	if (!cmd)
		exit (0);
	cmd->cmd_path = get_cmd_path(cmd->cmd[0], environ);
	if (execve(cmd->cmd_path, cmd->cmd, environ) == -1)
		error_exit(strerror(errno), NULL, NULL, 1);
}

/**
	* Executes executes either builtin, or non-builtin commands
	* @param data: minishell data;
	* @return VOID
*/
bool	execute_in_child(t_cmd *cmd_data, t_mini *mini_data)
{
	pid_t	pid;

	if (pipe(cmd_data->pipe_fd) == -1)
		error_exit(strerror(errno), NULL, NULL, 1);
	pid = fork();
	mini_data->last_pid = pid;
	if (pid == -1)
	{
		print_error("fork: ", strerror(errno), NULL);
		mini_data->exit_status = 1;
		return (false);
	}
	if (pid == 0)
	{
		if (cmd_data->cmd && is_builtin(cmd_data->cmd[0]))
		{
			execute_builtin(cmd_data, mini_data);
			exit (0);
		}
		else
			child_process(cmd_data, mini_data);
	}
	close (cmd_data->pipe_fd[WRITE_END]);
	dup2(cmd_data->pipe_fd[READ_END], STDIN_FILENO);
	close (cmd_data->pipe_fd[READ_END]);
	return (true);
}

void	execute_cmds(t_mini *data)
{
	t_cmd	*cmd_data;
	bool	set_exit;

	cmd_data = data->cmds;
	data->last_pid = -1;
	backup_std_in_and_out(data->std_backup);
	set_exit = true;
	while (cmd_data)
	{
		if (data->cmd_count == 1 && cmd_data->cmd
			&& is_builtin(cmd_data->cmd[0]))
		{
			execute_builtin(cmd_data, data);
			break ;
		}
		if (!execute_in_child(cmd_data, data))
		{
			set_exit = false;
			break ;
		}
		cmd_data = cmd_data->next;
	}
	wait_for_cmds(&data->exit_status, data->last_pid, set_exit);
	restore_std_in_and_out(data->std_backup);
}
