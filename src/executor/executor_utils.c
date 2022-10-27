/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 13:41:50 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/27 13:30:50 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strncmp(cmd, "echo", 5) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0
		|| ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "env", 4) == 0)
		return (true);
	return (false);
}

void	save_read_fd(t_cmd *current_command, int pipe_read_end)
{
	t_cmd	*next_command;

	next_command = current_command->next;
	if (next_command)
	{
		next_command->fd_in = dup(pipe_read_end);
		if (next_command->fd_in == -1)
			perror("dup:");
	}
}

void	backup_std_in_and_out(int backup[2])
{
	backup[READ_END] = dup(STDIN_FILENO);
	if (backup[READ_END] == -1)
		return (perror("dup2"), error_exit(NULL, 1));
	backup[WRITE_END] = dup(STDOUT_FILENO);
	if (backup[WRITE_END] == -1)
		return (perror("dup2"), error_exit(NULL, 1));
}

void	restore_std_in_and_out(int backup[2])
{
	if (dup2(backup[READ_END], STDIN_FILENO) == -1)
		return (perror("dup2"), error_exit(NULL, 1));
	if (dup2(backup[WRITE_END], STDOUT_FILENO) == -1)
		return (perror("dup2"), error_exit(NULL, 1));
	close(backup[READ_END]);
	close(backup[WRITE_END]);
}

