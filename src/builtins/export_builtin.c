/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_builtin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:31 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/15 22:17:33 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_key(char *env_var)
{
	char	*key;

	key = get_key_from_full_env_var(env_var);
	ft_putstr_fd(key, STDOUT_FILENO);
	free (key);
}

void	try_print_export_value(char *env_var)
{
	char	*value;

	value = get_value_from_full_env_var(env_var);
	if (!value)
		return ;
	ft_putchar_fd('=', STDOUT_FILENO);
	ft_putchar_fd('"', STDOUT_FILENO);
	ft_putstr_fd(value, STDOUT_FILENO);
	ft_putchar_fd('"', STDOUT_FILENO);
}

void	print_export(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		print_export_key(env[i]);
		try_print_export_value(env[i]);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

bool	is_valid_export(char *export)
{
	int	i;

	if (!ft_isalpha(export[0]) && export[0] != '_')
		return (false);
	i = 0;
	while (export[i])
	{
		if (export[i])
		i++;
	}
	return (true);
}

void	export_builtin(t_cmd *cmd, t_mini *data)
{
	char	**to_export;
	int		i;
	char	*key;
	char	*value;

	to_export = cmd->cmd;
	if (!to_export[1])
		print_export(data->env);
	else
	{
		i = 1;
		while (to_export[i])
		{
			if (is_valid_export(to_export[i]))
			{
				key = get_key_from_full_env_var(to_export[i]);
				value = get_value_from_full_env_var(to_export[i]);
				if (key_exists(data->env, key))
					set_key_value(data->env, key, value);
				else
					add_new_env_entry(&data->env, key, value);
				free (key);
			}
			else
				error_exit(key, ": not a valid identifier", NULL, 1);
			i++;
		}
	}
}

// export: `", s,
//				"': not a valid identifier"
// if starting with a number
// if starting with anything else then _ or alphabetic char