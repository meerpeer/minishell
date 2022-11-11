/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wait.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 09:54:49 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/11 14:02:46 by mevan-de      ########   odam.nl         */
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
void	wait_for_cmds(int *exit_status, pid_t pid)
{
	int status;

	waitpid(pid, &status, WUNTRACED);
	while (wait(NULL) > 0)
		continue ;
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
}
