/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 14:17:46 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/24 14:15:13 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
	* a function that creates a new string out of 3 other strings.
	* It doesn't free the original strings
	* @param s1 first string
	* @param s2 second string
	* @param s3 third string
	* @return newly allocated joined string
*/
char	*join_3_strings(char *s1, char *s2, char *s3)
{
	char *full_sentence;
	char *temp_join;

	full_sentence = protect_check(ft_strdup(s1));
	temp_join = protect_check(ft_strjoin(full_sentence, s2));
	free (full_sentence);
	full_sentence = protect_check(ft_strdup(temp_join));
	free (temp_join);
	temp_join = protect_check(ft_strjoin(full_sentence, s3));
	free (full_sentence);
	return (temp_join);
}

/**
	* Checks if the key already exists
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
	key = protect_check(ft_substr(full_str, 0, i);
	printf("the key = %s\n", key);
	return (key);
}

/**
	* Finds the pointer to the part where the value starts
	* Nothing allocated, don't free!
	* @param full_str the environment variable to check
	* @return one space after the '=' character
*/
char	*get_value_from_full_env_var(char *full_str)
{
	return (ft_strchr(full_str, '=') + 1);
}
