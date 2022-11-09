/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_quote.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 09:13:15 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/09 11:00:21 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_quote(char *word, int *i, t_word *word_copy, t_mini *mini_data)
{
	bool	should_expand;
	t_quote	quote_type;

	quote_type = get__quote_type(word[*i]);
	should_expand = false;
	if (quote_type == DOUBLE)
		should_expand = true;
	*i = *i + 1;
	while (word[*i])
	{
		quote_type = update_quote_type(quote_type, word[*i]);
		if (quote_type == NO_QUOTE)
			return ;
		if (should_expand && word[*i] == '$')
			expand_env(word, i, word_copy, mini_data);
		else
		{
			add_char_to_word_copy(word[*i], word_copy);
			*i = *i + 1;
		}
	}
}
