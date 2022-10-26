/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 09:11:46 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/26 09:12:55 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
	* a function that creates a new string out of 3 other strings.
	* It doesn't free the original strings. Joins from left to right, 
	* so if s2 = NULL, but s1 and s3 are valid, a dup of s1 will be returned, 
	* without s3 joined.
	* @note tested.
	* @param s1 first string
	* @param s2 second string
	* @param s3 third string
	* @return newly allocated joined string
*/
char	*join_3_strings(char *s1, char *s2, char *s3)
{
	char *full_sentence;
	char *temp_join;

	if (!s1)
		return (NULL);
	full_sentence = protect_check(ft_strdup(s1));
	if (!s2)
		return (full_sentence);
	temp_join = protect_check(ft_strjoin(full_sentence, s2));
	free (full_sentence);
	if (!s3)
		return (temp_join);
	full_sentence = protect_check(ft_strjoin(temp_join, s3));
	free (temp_join);
	return (full_sentence);
}
