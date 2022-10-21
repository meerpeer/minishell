/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mini_data.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 09:57:43 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/21 16:04:00 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
	* Should increment the shell level (SHLVL) in the environment variables. 
	* If there is none, it should be created!
	* @param *env environment variables from the main env;
	* @return the copied environment variables!
*/
void	update_shell_level(char **env)
{
	char	*sh_lvl_var;
	char	*temp;
	int		i;

	sh_lvl_var = get_env_var(env, "SHLVL");
	if (!sh_lvl_var)
		temp
}

/**
	* Copies the environment variables so we can use and manipulate them.
	* @param *env environment variables from the main env;
	* @return the copied environment variables!
*/
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
	copy_env[i] = NULL;
	return (copy_env);
}

void	init_mini_data(t_mini *data, char **env)
{
	//data = ft_calloc(1, sizeof(t_mini *));
	data->cmd_count = 0;
	data->cmd_index = 0;
	data->exit_status = 0;
	data->env = copy_env(env);
	//set SHLVL++;
	return ;
}
