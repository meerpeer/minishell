/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_builtin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:21:57 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/09 17:31:40 by lhoukes       ########   odam.nl         */
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

static int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static void	update_pwd(t_mini *data, char *new_path)
{
	new_path = getcwd(NULL, 0);
	set_key_value(data->env, "PWD", new_path);
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
	if (!cmd->cmd[1] || ft_strcmp(cmd->cmd[1], "~")== 0)
	{
		printf("new path[before home: %s]\n", new_path);
		go_to = chdir(get_env_var_value(data->env, "HOME"));
		//new_path = getcwd(NULL, 0);
		update_pwd(data, new_path);
		printf("new path[home: %s]\n", new_path);
		printf(G50"succesfully changed dir[home]\n"RESET);
	}
	else if (!cmd->cmd[2])
	{
		go_to = chdir(cmd->cmd[1]);
		printf("go_to [%d]\n", go_to);
		// new_path = getcwd(NULL, 0);
		update_pwd(data, new_path);
		printf("new path[current: %s]\n", new_path);
		printf(G50"succesfully changed dir[current]\n"RESET);
	}
	if (go_to == -1)
	{
		printf(R124"no can do: GO_TO error!\n"RESET);
		//should be a print error//
	}
	else
		printf(R124"dir changed\n"RESET);
	//printf("path = [%s]\n", path);
	
	// (void) data;
	//(void) cmd;
	free(new_path);
	printf("cd :D\n");
	//exit_status?//
	return ;
}

// else if (cmd->cmd[1] && ft_strncmp(cmd->cmd[1], "-", 1) == 0)
	// {
	// 	go_to = chdir(get_env_var_value(data->env, "OLDPDW"));
	// 	new_path = getcwd(NULL, 0);
	// 	printf("new path[previous: %s]\n", new_path);
	// 	update_pwd(data, new_path);
	// 	printf(G50"succesfully changed dir[previous]\n"RESET);
	// }
