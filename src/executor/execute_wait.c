/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_wait.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 09:54:49 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/17 13:31:20 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"
#include <stdio.h>

/*
	* Function that waits for a child command to be done.
	* @param *data: the shell t_mini information. Exit status will be updated.
	* @param *pid: the current process ID to wait for;
	* @return NOTHING
*/
void	wait_for_cmds(int *exit_status, pid_t pid, bool set_exit)
{
	int	status;

	waitpid(pid, &status, WUNTRACED);
	while (wait(NULL) > 0)
		continue ;
	if (WTERMSIG(status) == SIGQUIT)
	{
		g_exit_status = 128 + WTERMSIG(status);
		write(1, "\b\b  \b\b^\\Quit: 3\n", 16);
	}
	else if (WTERMSIG(status) == SIGINT)
	{
		g_exit_status = 128 + WTERMSIG(status);
		write(1, "\n", 1);
	}
	else if (WIFSIGNALED(status))
		*exit_status = WTERMSIG(status) + 128;
	else if (WIFEXITED(status) && set_exit)
		*exit_status = WEXITSTATUS(status);
}
