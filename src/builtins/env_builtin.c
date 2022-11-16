/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:22 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/16 15:30:58 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_mini *mini_data, char **cmd)
{
	int	i;

	if (!mini_data->env)
	{
		mini_data->exit_status = 1;
		return ;
	}
	else if (cmd && cmd[0] && cmd[1])
	{
		print_error("env: ", "too many arguments", NULL);
		mini_data->exit_status = 1;
		return ;
	}
	i = 0;
	while (mini_data->env[i])
	{
		if (is_variable_set(mini_data->env[i]))
			ft_putendl_fd(mini_data->env[i], STDOUT_FILENO);
		i++;
	}
	return ;
}
