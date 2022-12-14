/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_print_builtin.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 17:48:55 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/17 14:02:02 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_key(char *env_var)
{
	char	*key;

	key = get_key_from_full_env_var(env_var);
	ft_putstr_fd(key, STDOUT_FILENO);
	free (key);
}

static void	try_print_export_value(char *env_var)
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
	int		i;
	char	**sorted_env;

	i = 0;
	sorted_env = get_alphabetized_env(env);
	while (sorted_env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		print_export_key(sorted_env[i]);
		try_print_export_value(sorted_env[i]);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	free_2d_array_(sorted_env);
}
