/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_expand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 08:47:37 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/17 11:40:58 by mevan-de      ########   odam.nl         */
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
	if (word[i + size] && (word[i + size] == '?' || ft_isdigit(word[i + size])))
		return (1);
	while (word[i + size] && !is_white_space(word[i + size])
		&& ft_isalnum(word[i + size]))
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

static bool	check_is_only_expand_sign(char *word, int i, t_word *word_copy)
{
	if (!word[i] || word[i] == ' ' || word[i] == '\"')
	{
		add_char_to_word_copy('$', word_copy);
		return (true);
	}
	return (false);
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
void	expand_env(char *word, int *i, t_word *word_copy, t_mini *mini_data)
{
	int		size;
	char	*key;
	char	*value;

	*i = *i + 1;
	if (check_is_only_expand_sign(word, *i, word_copy))
		return ;
	size = get_key_size(*i, word);
	key = copy_key_to_str(*i, word, size);
	*i = *i + size ;
	if (ft_strncmp(key, "?", 1) == 0)
	{
		value = protect_check(ft_itoa(g_exit_status));
		free(key);
		copy_value_to_word(value, word_copy);
		free(value);
		return ;
	}
	value = get_env_var_value(mini_data->env, key);
	free (key);
	if (!value)
		return ;
	copy_value_to_word(value, word_copy);
}
