/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mini_data.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 09:57:43 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/16 18:00:32 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
	* Should increment the shell level (SHLVL) in the environment variables. 
	* If there is none, it should be created!
	* @param *env environment variables from the main env;
	* @return the copied environment variables!
*/
void	update_shell_level(t_mini *mini_data)
{
	char	*old_value;
	char	*new_value;
	int		converted_value;

	if (!key_exists(mini_data->env, "SHLVL"))
		add_new_env_entry(mini_data, "SHLVL", "1");
	else
	{
		old_value = get_env_var_value(mini_data->env, "SHLVL");
		converted_value = ft_atoi(old_value);
		converted_value++;
		new_value = protect_check(ft_itoa(converted_value));
		set_key_value(mini_data->env, "SHLVL", new_value);
		free(new_value);
	}
}

/**
	* Copies the environment variables so we can use and manipulate them.
	* @param *env environment variables from the main env;
	* @return the copied environment variables!
*/
char	**copy_env(void)
{
	int			i;
	extern char	**environ;
	char		**copy_env;

	i = 0;
	copy_env = ft_calloc(get_count_env_vars(environ) + 1, sizeof(char *));
	if (!copy_env)
		error_exit("environment variable copy failed\n", NULL, NULL, 1);
	while (environ[i])
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

	data = ft_calloc(1, sizeof(t_mini));
	data->cmd_count = 0;
	data->cmd_index = 0;
	data->exit_status = 0;
	data->cmds = NULL;
	data->tokens = NULL;
	data->env = copy_env();
	set_key_value(data->env, "OLDPWD", NULL);
	update_shell_level(data);
	return (data);
}
