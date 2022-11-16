/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_utiles.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 07:50:08 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/16 09:53:19 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_char(char c)
{
	if (c == '\n' || c == '\t' || c == '\v' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

t_quote	get_quote_type(char c)
{
	if (c == '\'')
		return (SINGLE);
	else if (c == '\"')
		return (DOUBLE);
	return (NO_QUOTE);
}

int	word_count(char *str)
{
	int		index;
	int		words;
	t_quote	quote_type;

	quote_type = NO_QUOTE;
	if (!str)
		return (0);
	words = 0;
	index = 0;
	while (str[index] != '\0')
	{
		if (quote_type == NO_QUOTE)
			quote_type = get_quote_type(str[index]);
		else if (quote_type == get_quote_type(str[index]))
			quote_type = NO_QUOTE;
		if (quote_type == NO_QUOTE || str[index + 1] == '\0')
		{
			if (find_char(str[index]) == 0 && \
			(find_char(str[index + 1]) == 1 || str[index + 1] == '\0'))
				words++;
		}
		index++;
	}
	return (words);
}

int	word_len(char *str, int tracker)
{
	int		word_len;
	t_quote	quote_type;

	quote_type = NO_QUOTE;
	word_len = 0;
	if (!str)
		return (0);
	while (str[tracker] != '\0')
	{
		if (quote_type == NO_QUOTE)
			quote_type = get_quote_type(str[tracker]);
		else if (quote_type == get_quote_type(str[tracker]))
			quote_type = NO_QUOTE;
		if (find_char(str[tracker]) == 1 && quote_type == NO_QUOTE)
			break ;
		tracker++;
		word_len++;
	}
	return (word_len);
}

void	chop_loop(char **strptr, int x, char *str, int *index)
{
	int	y;
	int	word_end_index;

	y = 0;
	word_end_index = word_len(str, *index) + *index;
	while (*index < word_end_index && str[*index] != '\0')
	{
		strptr[x][y] = str[*index];
		y++;
		*index = *index + 1;
	}
	strptr[x][y] = '\0';
}
