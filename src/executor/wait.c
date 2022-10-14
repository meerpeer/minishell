/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wait.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 09:54:49 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/14 10:22:27 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"

/*
	* Function that waits for a child command to be done.
	* @param *data: the shell t_mini information. Exit status will be updated.
	* @param *pid: the current process ID to wait for;
	* @return NOTHING
*/
void	wait_for_cmd(t_mini *data, pid_t pid)
{
	int status;

	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	// WIFSIGNALED should also be used?! if something is killed by ctrl+c or something?
	// fuck I don't know.. what would the error code even be? find out.
}
