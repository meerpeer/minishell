/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_change.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 11:41:05 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/23 14:24:12 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this file contains the add entry and delete entry

/**
	* frees the key entry and shifts all the other entries after it one down.
	* @param env the environment variables
	* @param key they environment variable name
	* @return nothing
*/
void	delete_env_entry(char **env, char *key)
{
	int	i;

	i = 0;
	if (!env || !key)
		return ;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)))
		{
			free (env[i]);
			break ;
		}
		i++;
	}
	while (env[i] && env[i + 1])
	{
		env[i] = protect_check(ft_strdup(env[i + 1]));
		i++;
	}
	env[i] = NULL;
}

/**
	* Changes the value of a key if it exists
	* @param env the environment variables
	* @param key the existing name of the variable
	* @param value the new value of the variable
	* @return nothing
*/
void	set_key_value(char **env, char *key, char *value)
{
	int		i;
	char	*key_equals;
	char	*new_value;

	i = get_env_var_index(env, key);
	if (i == -1)
		return ; //means key not found
	key_equals = protect_check(ft_strjoin(key, "="));
	printf("key_equals = %s\n", key_equals);
	free (key_equals);
//	return ;
	new_value = protect_check(ft_strjoin(key_equals, value));
	env[i] = (char *)protect_check(ft_strdup(new_value));
	free (new_value);
	return ; // REMOVE ME
}

/**
	* Creates a new env variable based on the key and appends it to a copy of the
	* original list, with one extra space for the new variable. Frees the old array.
	* @param env the environment variables
	* @param key the new variable name to be added.
	* @param value optional value to be set instantly, NULL if there is no value
	* @return nothing
*/
void	new_env_entry(char ***env, char *key, char *value)
{
	int		i;
	int		original_size;
	char	**new_env;
(void) value;
	//add check to see if exists
	original_size = get_count_env_vars(*env);
	new_env = protect_check(ft_calloc(original_size + 1, sizeof(char **)));
	i = 0;
	while (env[i])
	{
		new_env[i] = protect_check(ft_strdup(*env[i]));
		free (env[i]);
		i++;
	}
	new_env[i] = protect_check(ft_strjoin(key, "="));
	new_env[i + 1] = NULL;
	if (value)
		set_key_value(*env, key, value);
	free(*env);
	*env = new_env;
}
