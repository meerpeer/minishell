/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:22 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/24 08:05:00 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_mini *mini_data)
{
	int		i;
	char	*all_env;
	char	*join;

	join = NULL;
	all_env = protect_check(ft_strdup(mini_data->env[0]));
	i = 1;
	while(mini_data->env[i])
	{
		join = join_3_strings(all_env, mini_data->env[i], "\n");
		free(all_env);
		all_env = protect_check(ft_strdup(join));
		free (join);
		i++;
	}
	printf("%s", all_env);
	free (all_env);
	return ;
}
