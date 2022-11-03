/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merel <merel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:58:39 by merel             #+#    #+#             */
/*   Updated: 2022/11/03 12:39:12 by merel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief checks if too much memory was allocated and creates a perfectly 
 * allocated char * if needed
 * 
 * @param word_copy the copied word with it's word length and allocated size
 */
void	reallocate_to_word_length(t_word *word_copy)
{
	char	*old_word;
	int		i;

	if (word_copy->malloced == word_copy->word_length)
		return ;
	old_word = word_copy->word;
	word_copy->word = protect_check(
						ft_calloc(word_copy->word_length + 2, sizeof(char)));
	i = 0;
	while (i < word_copy->word_length)
	{
		word_copy->word[i] = old_word[i];
		i++;
	}
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
		while (i <  word_copy->word_length)
		{
			word_copy->word[i] = old_word[i];
			i++;
		}
		free (old_word);
	}
	word_copy->word[word_copy->word_length - 1] = c;
}

/**
 * @brief should expand the environment variable if it's there and should
 * increment i past the env variable;
 * 
 * TODO: try to get env in here
 * TODO: test!
 * @param word the original string 
 * @param i the index on the original string
 * @param word_copy where we copy the new word into
 */
void	expand_env(char *word, int *i, t_word *word_copy, char **env)
{
	int		j;
	int		size;
	char	*key;
	char	*value;

	*i = *i + 1;
	size = 0;
	while (word[*i + size] && !is_white_space(word[*i + size]) && word[*i + size] != '\"')
		size++;
	key = protect_check(ft_calloc(size + 1, sizeof(char)));
	j = 0;
	while (j < size)
	{
		key[j] = word[*i];
		*i = *i + 1;
		j++;
	}
	value = get_env_var_value(env, key);
	free (key);
	if (!value)
		return;
	j = 0;
	while (value[j])
	{
		add_char_to_word_copy(value[j], word_copy);
		j++;
	}
}

void	loop_quote(char *word, int *i, t_word *word_copy, char **env)
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
			expand_env(word, i, word_copy, env);
		else
		{
			add_char_to_word_copy(word[*i], word_copy);
			*i = *i + 1;
		}
	}
}

/**
	TODO: test!
*/
bool	try_parse_word(char *word, t_cmd *cmd, char **env)
{
	int		i;
	t_word	*word_copy;
	t_quote	quote_type;

	i = 0;
	quote_type = NO_QUOTE;
	word_copy = protect_check(ft_calloc(1, sizeof(t_word)));
	word_copy->word = protect_check(ft_calloc(8, sizeof(t_word)));
	word_copy->malloced = 8;
	while (word[i])
	{
		quote_type = update_quote_type(quote_type, word[i]);
		if (quote_type != NO_QUOTE)
			loop_quote(word, &i, word_copy, env);
		else if (word[i] == '$')
			expand_env(word, &i, word_copy, env);
		else
			add_char_to_word_copy(word[i], word_copy);
		quote_type = update_quote_type(quote_type, word[i]);
		i++;
	}
	if (quote_type != NO_QUOTE)
	{
		free(word_copy->word);
		return (printf("syntax error: multiline command"), false);
	}
	reallocate_to_word_length(word_copy);
	add_to_2d_array(&cmd->cmd, word_copy->word);
	free(word_copy->word);
	return (true);
}
