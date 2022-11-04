/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_builtin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:21:57 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/04 14:58:57 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//change dir functie
// OLDPATH opslaan/ current path in PATH
// bij binnenkomst minishell - OLDPATH & PATH update??
// placeholder pwd = getcwd 
// als nog niet bestaat : oldpwd set value = pwd
// als wel delete en set new oldpwd
// chdir 
// delete current PWD
// pwd = getcwd 
// add new PWD; 

//callo or malloc for new_path?? 

static void	update_pwd(t_mini *data, char *new_path)
{
	delete_env_entry(data->env, "PWD");
	add_new_env_entry(&data->env, "PWD", new_path);
}

void	cd_builtin(t_cmd *cmd, t_mini *data)
{
	int		go_to;
	char 	*new_path;

	go_to = 0;
	
	new_path = getcwd(NULL, 0);
	if (!key_exists(data->env, "OLDPWD"))
		add_new_env_entry(&data->env, "OLDPWD", new_path);
	else
		set_key_value(data->env, "OLDPWD", get_env_var_value(data->env, "PWD"));
	if (!cmd->cmd[1] || ft_strncmp(cmd->cmd[1], "~", 1) == 0)
	{
		go_to = chdir(get_env_var_value(data->env, "HOME"));
		new_path = getcwd(NULL, 0);
		update_pwd(data, new_path);
		printf(G50"succesfully changed dir[home]\n"RESET);
	}
		//path = get_env_var_value(data->env, "HOME");
	// else if (!cmd->cmd[2])
	// {
	// 	//set_key_value(data->env, "OLDPWD", get_env_var_value(data->env, "PWD"));
	// 	go_to = chdir(cmd->cmd[1]);
	// 	printf(G50"succesfully changed dir[current]\n"RESET);
	// }
		
	// else if (cmd->cmd[1] && ft_strncmp(cmd->cmd[1], "-", 1) == 0)
	// {
	// 	go_to = chdir(get_env_var_value(data->env, "OLDPDW"));
	// 	printf(G50"succesfully changed dir[previous]\n"RESET);
	// }
	else
		printf(R124"no can do!\n"RESET);
	//printf("path = [%s]\n", path);
	
	// (void) data;
	(void) cmd;
	free(new_path);
	printf("cd :D\n");
	return ;
}
