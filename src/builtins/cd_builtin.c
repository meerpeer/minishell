/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_builtin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:21:57 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/15 22:11:16 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(char *s1, char *s2)
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
	if (key_exists(data->env, "PWD"))
		set_key_value(data->env, "PWD", new_path);
	free(new_path);
}

void	cd_builtin(t_cmd *cmd, t_mini *data)
{
	int		go_to;
	char	*new_path;
	char	*empty;

	empty = " ";

	go_to = 0;
	new_path = getcwd(NULL, 0);
	if (key_exists(data->env, "PWD"))
		set_key_value(data->env, "OLDPWD", new_path);
	else
	{
		set_key_value(data->env, "OLDPWD", empty);
		printf("pwd does not exixt\n");
	} 
		
	if (!cmd->cmd[1] || (ft_strcmp(cmd->cmd[1], "cd") == 0 && !cmd->cmd[2]))
	{
		if (!key_exists(data->env, "HOME"))
		{
			printf("minshell: cd: HOME not set\n");
			return ;
		}
		go_to = chdir(get_env_var_value(data->env, "HOME"));
		update_pwd(data, new_path);
	}
	else if (!cmd->cmd[2])
	{
		go_to = chdir(cmd->cmd[1]);
		update_pwd(data, new_path);
	}
	if (go_to == -1)
		printf(R124"no can do: GO_TO error!\n"RESET);
	else
		printf(R124"dir changed\n"RESET);
	free(new_path);
}
// need to set OLDPWD to "OLDPWD= " is PWD is unset