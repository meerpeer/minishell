/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merel <merel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:58:39 by merel             #+#    #+#             */
/*   Updated: 2022/10/31 12:35:46 by merel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reallocate_to_word_length(t_word *word_copy)
{
	char	*old_word;
	int		i;

	if (word_copy->malloced == word_copy->word_length)
		return ;
	old_word = word_copy->word;
	word_copy->word = protect_check(
						ft_calloc(word_copy->word_length, sizeof(char)));
	i = 0;
	while (i < word_copy->word_length)
	{
		word_copy->word[i] = old_word[i];
		i++;
	}
	free (old_word);
}

void	add_char_to_word_copy(char c, t_word *word_copy)
{
	char	*old_word;
	int		i;

	if (!c)
		return ;
	word_copy->word_length++;
	i = 0;
	if (word_copy->malloced < word_copy->word_length)
	{
		old_word = word_copy->word;
		word_copy->malloced *= 2;
		word_copy->word = protect_check(
							ft_calloc(word_copy->malloced, sizeof(char)));
		i = 0;
		while (i <  word_copy->word_length)
		{
			word_copy->word[i] = old_word[i];
			i++;
		}
		free (old_word);
	}
	word_copy->word[word_copy->word_length - 1] = c;
}

void	loop_quote(char *word, int *i, t_word *word_copy, t_quote *quote_type)
{
	bool	should_expand;

	should_expand = false;
	if (*quote_type == DOUBLE)
		should_expand = true;
	*i = *i + 1;
	while (word[*i])
	{
		*quote_type = update_quote_type(*quote_type, word[*i]);
		if (*quote_type == NO_QUOTE)
			return ;
		if (should_expand && word[*i] == '$')
			//expand! yay
		add_char_to_word_copy(word[*i], word_copy);
		*i = *i + 1;
	}
}

/**
	TODO: test!
*/
bool	try_parse_word(char	*word, t_cmd *cmd)
{
	int		i;
	t_word	word_copy;
	t_quote	quote_type;

	i = 0;
	quote_type = NO_QUOTE;
	//word_copy = protect_check(ft_calloc(1, sizeof(word_copy)));
	while (word[i])
	{
		quote_type = update_quote_type(quote_type, word[i]);
		if (quote_type != NO_QUOTE)
			loop_quote(word, &i, &word_copy, &quote_type);
		else
			add_char_to_word_copy(word[i], &word_copy);
		i++;
	}
	if (quote_type != NO_QUOTE)
	{
		free(word_copy.word);
		return (printf("syntax error: multiline command"), false);
	}
	reallocate_to_word_length(&word_copy);
	add_to_2d_array(&cmd->cmd, word_copy.word);
	free(word_copy.word);
	return (true);
}
