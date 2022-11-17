/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_sort.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 13:57:24 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/17 14:49:40 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(char **env, int first, int second)
{
	char	*temp;

	temp = env[first];
	env[first] = env[second];
	env[second] = temp;
}

static char	**get_env_copy(char **env)
{
	char	**env_copy;
	int		i;
	int		size;

	size = get_count_env_vars(env);
	env_copy = protect_check(ft_calloc(size + 1, sizeof(char *)));
	i = 0;
	while (env[i])
	{
		env_copy[i] = protect_check(ft_strdup(env[i]));
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

char	**get_alphabetized_env(char **env)
{
	char	**alpha_env;
	int		size;
	int		i;

	alpha_env = get_env_copy(env);
	size = get_count_env_vars(env);
	while (size > 0)
	{
		i = 0;
		while (alpha_env[i] && alpha_env[i + 1])
		{
			if (ft_strcmp (alpha_env[i], alpha_env[i + 1]) > 0)
				swap(alpha_env, i, i + 1);
			i++;
		}
		size--;
	}
	return (alpha_env);
}
