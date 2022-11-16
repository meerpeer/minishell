/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_word.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 10:58:39 by merel         #+#    #+#                 */
/*   Updated: 2022/11/16 10:53:33 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief checks if too much memory was allocated and creates a perfectly 
 * allocated char * if needed
 * 
 * @param word_copy the copied word with it's word length and allocated size
 */
static void	reallocate_to_word_length(t_word *word_copy)
{
	char	*old_word;
	int		i;

	if (word_copy->malloced <= word_copy->word_length - 1)
		return ;
	old_word = word_copy->word;
	word_copy->word = protect_check(
			ft_calloc(word_copy->word_length + 1, sizeof(char)));
	i = 0;
	while (i < word_copy->word_length)
	{
		word_copy->word[i] = old_word[i];
		i++;
	}
	word_copy->word[i] = '\0';
	free (old_word);
}

/**
 * @brief should store the character in the word_copy->word
 * 
 * @param c character to add to the word
 * @param word_copy the place the character should be copied to
 */
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
		while (i < word_copy->word_length)
		{
			word_copy->word[i] = old_word[i];
			i++;
		}
		free (old_word);
	}
	word_copy->word[word_copy->word_length - 1] = c;
}

static t_word	*init_word_copy(void)
{
	t_word	*word_copy;

	word_copy = protect_check(ft_calloc(1, sizeof(t_word)));
	word_copy->word = protect_check(ft_calloc(8, sizeof(t_word)));
	word_copy->malloced = 8;
	return (word_copy);
}

static bool	copy_word(t_word *word_copy, char *word, t_mini *mini_data)
{
	int		i;
	t_quote	quote_type;

	i = 0;
	quote_type = NO_QUOTE;
	while (word[i])
	{
		quote_type = update_quote_type(quote_type, word[i]);
		if (quote_type != NO_QUOTE)
			loop_quote(word, &i, word_copy, mini_data);
		else if (word[i] == '$')
		{
			expand_env(word, &i, word_copy, mini_data);
			continue ;
		}
		else
			add_char_to_word_copy(word[i], word_copy);
		if (!word[i])
			break ;
		quote_type = update_quote_type(quote_type, word[i]);
		i++;
	}
	if (quote_type == NO_QUOTE)
		return (true);
	return (print_error("syntax error: multiline command", NULL, NULL), false);
}

/**
	TODO: test!
*/
bool	try_parse_word(char *word, t_cmd *cmd, t_mini *mini_data)
{
	t_word	*word_copy;
	bool	quotes_complete;

	word_copy = init_word_copy();
	quotes_complete = copy_word(word_copy, word, mini_data);
	reallocate_to_word_length(word_copy);
	add_to_2d_array(&cmd->cmd, word_copy->word);
	free(word_copy->word);
	free(word_copy);
	if (quotes_complete)
		return (true);
	return (false);
}
