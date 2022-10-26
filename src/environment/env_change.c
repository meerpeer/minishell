/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_change.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 11:41:05 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/26 11:50:57 by mevan-de      ########   odam.nl         */
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
	int		i;

	if (!env || !key)
		return ;
	i = get_env_var_index(env, key);
	if (i == -1)
		return ;
	free (env[i]);
	while (env[i + 1])
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
}

/**
	* Changes the value of a key if it exists. 
	* If the key doesn't exist, it returns without setting anything.
	* @param env the environment variables
	* @param key the existing name of the variable
	* @param value the new value of the variable
	* @return nothing
*/
void	set_key_value(char **env, char *key, char *value)
{
	int		i;
	char	*new_entry;

	printf("setting %s to value: %s\n", key, value);
	i = get_env_var_index(env, key);
	printf("env index = %i\n", i);
	if (i == -1)
		return ;
	new_entry = join_3_strings(key, "=", value);
	free (env[i]);
	env[i] = (char *)protect_check(ft_strdup(new_entry));
	printf("env[i] = %s\n", env[i]);
	free (new_entry);
	return ;
}

/**
	* Creates a new env variable based on the key and appends it to a copy of the
	* original list, with one extra space for the new variable. Frees the old array.
	* @note tested
	* @param env the environment variables
	* @param key the new variable name to be added.
	* @param value optional value to be set instantly, NULL if there is no value
	* @return nothing
*/
void	add_new_env_entry(char ***env, char *key, char *value)
{
	int		i;
	int		original_size;
	char	**new_env;
	char	**old_env;

	old_env = *env;
	original_size = get_count_env_vars(old_env);
	new_env = protect_check(ft_calloc(original_size + 1, sizeof(char **)));
	i = 0;
	while (old_env[i])
	{
		new_env[i] = protect_check(ft_strdup(old_env[i]));
		free(old_env[i]);
		printf ("---- new_env[%i] = %s\n", i, new_env[i]);
		i++;
	}
	new_env[i] = protect_check(ft_strjoin(key, "="));
	new_env[i + 1] = NULL;
	if (value)
		set_key_value(new_env, key, value);
	free(*env);
	*env = new_env;
}
