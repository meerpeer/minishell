/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mini_data.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 09:57:43 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/18 11:55:36 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **env)
{
	int		i;
	char	**copy_env;

	i = 0;
	copy_env = ft_calloc(get_count_env_vars(env) + 1, sizeof(char **));
	if (!copy_env)
		return (NULL); // error exit. "environment copy failed"
	while(env[i])
	{
		copy_env[i] = ft_strdup(env[i]);
		if (!copy_env[i])
			return (NULL); // again error exit "environment copy failed"
		i++;
	}
	return (copy_env);
}

void	init_mini_data(t_mini *data, char **env)
{
	data->cmd_count = 0;
	data->cmd_index = 0;
	data->exit_status = 0;
	data->env = copy_env(env);
	//set SHLVL++;
	return ;
}
