/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_change.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 11:41:05 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/23 12:03:26 by mevan-de      ########   odam.nl         */
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
		env[i] = ft_strdup(env[i + 1]);
		if (!env[i])
			exit (1);
		i++;
	}
	env[i] = NULL;
}

/**
	* Creates a new env variable based on the key and appends it to a copy of the
	* original list, with one extra space for the new variable. Frees the old array.
	* @param env 
	* @return nothing
*/
void	new_env_entry(char ***env, char *key)
{
	int		i;
	int		original_size;
	char	**new_env;

	original_size = get_count_env_vars(*env);
	new_env = ft_calloc(original_size + 1, sizeof(char **));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(*env[i]);
		if (!new_env[i])
			exit (1);
		free (env[i]);
		i++;
	}
	new_env[i] = ft_strdup(ft_strjoin(key, "="));
	if (!new_env[i])
		exit (1);
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
}
