/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_for_tokens.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 21:31:06 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/15 21:34:27 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**chop_str(char *str, char **strptr, int words)
{
	int	index;
	int	x;

	if (!str)
		return (0);
	index = 0;
	x = 0;
	while (str[index] != '\0' && x < words)
	{
		while (find_char(str[index]) == 1)
			index++;
		strptr[x] = protect_check((char *)malloc(sizeof(char) \
			* word_len(str, index) + 1));
		chop_loop(strptr, x, str, &index);
		x++;
	}
	strptr[x] = NULL;
	return (strptr);
}

char	**split(char *str)
{
	char	**strptr;
	int		words;

	if (str == NULL)
		return (NULL);
	words = word_count(str);
	strptr = protect_check((char **)malloc(sizeof (char *) * (words + 1)));
	if (strptr == NULL)
		return (NULL);
	return (chop_str(str, strptr, words));
}
