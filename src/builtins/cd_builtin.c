/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_builtin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:21:57 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/03 17:53:44 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//change dir functie

// OLDPATH opslaan/ current path in PATH

// bij binnenkomst minishell - OLDPATH & PATH update??


void	cd_builtin(t_cmd *cmd, t_mini *data)
{
	char *path;
	// if statement checks for cmd->cmd[0] cmd->cmd[1][0]
	path = get_env_var_value(data->env, "HOME");
	printf("path = [%s]\n", path);
	
	// (void) data;
	(void) cmd;
	printf("cd :D\n");
	return ;
}
