/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 14:17:46 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/24 08:01:08 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_3_strings(char *s1, char *s2, char *s3)
{
	char *full_sentence;
	char *temp_join;

	printf("entered\n");
	full_sentence = protect_check(ft_strdup(s1));
	printf("succes\n");
	temp_join = protect_check(ft_strjoin(full_sentence, s2));
	free (full_sentence);
	printf("succes\n");
	full_sentence = protect_check(ft_strdup(temp_join));
	printf("succes\n");
	free (temp_join);
	temp_join = protect_check(ft_strjoin(full_sentence, s3));
	printf("succes\n");
	free (full_sentence);
	return (temp_join);
}