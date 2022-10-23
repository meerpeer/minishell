/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mini_data.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 09:57:43 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/23 14:14:07 by mevan-de      ########   odam.nl         */
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
	//int		i;

	sh_lvl_var = get_env_var_value(env, "SHLVL");
	if (!sh_lvl_var)
		new_env_entry(&env, "SHLVL", "1");
}

/**
	* Copies the environment variables so we can use and manipulate them.
	* @param *env environment variables from the main env;
	* @return the copied environment variables!
*/
char	**copy_env()
{
	int			i;
	extern char	**environ;
	char		**copy_env;
	
	i = 0;
	copy_env = ft_calloc(get_count_env_vars(environ) + 1, sizeof(char *));
	if (!copy_env)
		error_exit("environment variable copy failed", 1);
	while(environ[i])
	{
		copy_env[i] = protect_check(ft_strdup(environ[i]));
		i++;
	}
	copy_env[i] = NULL;
	return (copy_env);
}

t_mini	*init_mini_data(void)
{
	t_mini	*data;

	data = ft_calloc(1, sizeof(t_mini *));
	data->cmd_count = 0;
	data->cmd_index = 0;
	data->exit_status = 0;
	data->env = copy_env();

	//printf("JUST TRYING SOMETHING: %s\n\n", data->env[0]);
	return (data);
}
