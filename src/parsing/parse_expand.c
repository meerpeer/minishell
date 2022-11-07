/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_expand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 08:47:37 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/07 09:06:17 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_value_to_word(char *value, t_word *word_copy)
{
	int	j;

	j = 0;
	while (value[j])
	{
		add_char_to_word_copy(value[j], word_copy);
		j++;
	}
}

static int	get_key_size(int i, char *word)
{
	int	size;

	size = 0;
	while (word[i + size] && !is_white_space(word[i + size])
		&& word[i + size] != '\"')
		size++;
	return (size);
}

static char	*copy_key_to_str(int i, char *word, int size)
{
	char	*key;
	int		j;

	key = protect_check(ft_calloc(size + 1, sizeof(char)));
	j = 0;
	while (j < size)
	{
		key[j] = word[i + j];
		j++;
	}
	return (key);
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
	int		size;
	char	*key;
	char	*value;

	*i = *i + 1;
	size = get_key_size(*i, word);
	key = copy_key_to_str(*i, word, size);
	*i = *i + size;
	value = get_env_var_value(env, key);
	free (key);
	if (!value)
		return ;
	copy_value_to_word(value, word_copy);
}
