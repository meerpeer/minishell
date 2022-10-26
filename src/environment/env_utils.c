/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 14:17:46 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/26 11:29:18 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
	* Checks if the key already exists
	* @note tested.
	* @param env the environment variables to check
	* @param key the key word to look for
	* @return true if the key was found, false if it wasn't found
*/
bool	key_exists(char **env, char *key)
{
	if (!key || get_env_var_index(env, key) == -1)
		return (false);
	return (true);
}

/**
	* Finds the key part and returns a newly allocated string
	* Make sure to free the pointer when done with it.
	* @note tested!
	* @param full_str the environment variable to check
	* @return Allocated string with just the key (no '=')
*/
char	*get_key_from_full_env_var(char *full_str)
{
	int		i;
	char	*key;
	
	i = 0;
	key = NULL;
	while (full_str[i] && full_str[i] != '=')
		i++;
	key = protect_check(ft_substr(full_str, 0, i));
	return (key);
}

/**
	* Finds the pointer to the part where the value starts
	* Nothing allocated, don't free!
	* @note tested
	* @param full_str the environment variable to check
	* @return one space after the '=' character
*/
char	*get_value_from_full_env_var(char *full_str)
{
	char	*value;

	value = ft_strchr(full_str, '=');
	if (!value || value[1] == '\0')
		return (NULL);
	return (&value[1]);
}

bool	is_variable_set(char *env_variable)
{
	if (get_value_from_full_env_var(env_variable))
		return (true);
	return (false);
}
