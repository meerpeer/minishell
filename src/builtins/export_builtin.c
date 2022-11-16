/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_builtin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:31 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/16 17:58:18 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_export(char *export)
{
	int		i;
	char	*key;

	if (!ft_isalpha(export[0]) && export[0] != '_')
		return (false);
	i = 0;
	while (export[i])
	{
		if (export[i])
			i++;
	}
	key = get_key_from_full_env_var(export);
	if (!key)
		return (false);
	i = 0;
	while (key[i]
		&& (ft_isalpha(key[i]) || ft_isdigit(key[i]) || key[i] == '+'))
		i++;
	if (key[i])
	{
		free (key);
		return (false);
	}
	free (key);
	return (true);
}

static void	export_argument(char *cmd, t_mini *data)
{
	char	*key;
	char	*value;

	key = get_key_from_full_env_var(cmd);
	if (is_valid_export(cmd))
	{
		value = get_value_from_full_env_var(cmd);
		if (key_exists(data->env, key))
			set_key_value(data->env, key, value);
		else
			add_new_env_entry(data, key, value);
	}
	else
	{
		print_error(key, ": not a valid identifier", NULL);
		data->exit_status = 1;
	}
	free (key);
}

void	export_builtin(t_cmd *cmd, t_mini *data)
{
	int		i;

	if (!cmd->cmd[1])
		print_export(data->env);
	else
	{
		i = 1;
		while (cmd->cmd[i])
		{
			export_argument(cmd->cmd[i], data);
			i++;
		}
	}
}
