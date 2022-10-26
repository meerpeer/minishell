/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_gets.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 11:43:46 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/26 11:24:05 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
	* Finds the environment variable value based on a key. 
	* Only searches from the start of every str in env, until key_length; 
	* @note Tested
	* @param env: the environment variables to check
	* @param key: the key word used to search env
	* @return the pointer to the place where the variable starts, 
	* without the key word.
*/
char	*get_env_var_value(char **env, char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
		{
			if (env[i][key_len] == '=' && env[i][key_len + 1])
				return (&env[i][key_len + 1]);
		}
		i++;
	}
	return (NULL);
}

/**
	* Finds the environment variable index based on a key. 
	* Only searches from the start of every str in env, until key_length;
	* @param env: the environment variables to check
	* @param key: the key word used to search env
	* @return index on succes, -1 on not found;
*/
int	get_env_var_index(char **env, char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
		{
			if (env[i][key_len] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

/**
	* Gets how many env variables are in env, 
	* useful for memory allocation!
	* @param env: the environment variables to check;
	* @return number of variables
*/
int	get_count_env_vars(char **env)
{
	int	count;

	count = 0;
	if (!env)
		return (0);
	while (env[count])
		count++;
	return (count);
}
