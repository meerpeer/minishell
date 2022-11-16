/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_builtin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:21:57 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/16 14:11:59 by mevan-de      ########   odam.nl         */
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

static void	check_if_key_exist(t_mini *data, char *new_path)
{
	char	*empty;

	empty = " ";
	if (key_exists(data->env, "PWD"))
		set_key_value(data->env, "OLDPWD", new_path);
	else
	{
		set_key_value(data->env, "OLDPWD", empty);
		printf("pwd does not exist\n");
	}
}

void	cd_builtin(t_cmd *cmd, t_mini *data)
{
	int		go_to;
	char	*new_path;

	go_to = 0;
	new_path = getcwd(NULL, 0);
	check_if_key_exist(data, new_path);
	if (!cmd->cmd[1] || (ft_strcmp(cmd->cmd[1], "cd") == 0 && !cmd->cmd[2]))
	{
		if (!key_exists(data->env, "HOME"))
		{
			print_error(cmd->cmd[0], ": HOME not set", NULL);
			data->exit_status = 1;
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
	{
		print_error(strerror(errno), NULL, NULL);
		data->exit_status = 1;
	}
	free(new_path);
}
// need to set OLDPWD to "OLDPWD= " is PWD is unset