/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_builtin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:21:57 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/17 17:58:53 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_mini *data, char *curr_path)
{
	curr_path = getcwd(NULL, 0);
	if (key_exists(data->env, "PWD"))
		set_key_value(data->env, "PWD", curr_path);
	free(curr_path);
}

static void	update_oldpwd(t_mini *data, char *curr_path)
{
	char	*empty;

	empty = " ";
	if (key_exists(data->env, "PWD"))
	{
		if (key_exists(data->env, "OLDPWD"))
			set_key_value(data->env, "OLDPWD", curr_path);
		else
			add_new_env_entry(data, "OLDPWD", curr_path);
	}
	else
	{
		if (key_exists(data->env, "OLDPWD"))
			set_key_value(data->env, "OLDPWD", empty);
		else
			add_new_env_entry(data, "OLDPWD", empty);
	}
}

static void	take_me_home(t_cmd *cmd, t_mini *data, char *curr_path)
{
	int	go_to;

	go_to = 0;
	if (!key_exists(data->env, "HOME"))
	{
		print_error(cmd->cmd[0], ": HOME not set", NULL);
		g_exit_status = 1;
		return ;
	}
	go_to = chdir(get_env_var_value(data->env, "HOME"));
	update_pwd(data, curr_path);
}

void	cd_builtin(t_cmd *cmd, t_mini *data)
{
	int		go_to;
	char	*curr_path;

	go_to = 0;
	curr_path = getcwd(NULL, 0);
	update_oldpwd(data, curr_path);
	if (!cmd->cmd[1] || (ft_strcmp(cmd->cmd[1], "cd") == 0 && !cmd->cmd[2]))
		take_me_home(cmd, data, curr_path);
	else if (!cmd->cmd[2])
	{
		go_to = chdir(cmd->cmd[1]);
		update_pwd(data, curr_path);
	}
	if (go_to == -1)
	{
		print_error(strerror(errno), NULL, NULL);
		g_exit_status = 1;
	}
	free(curr_path);
}
