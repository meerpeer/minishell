/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 14:17:46 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/24 08:46:16 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	key_exists(char **env, char *key)
{
	if (!key || get_env_var_index(env, key) == -1)
		return (false);
	return (true);
}
