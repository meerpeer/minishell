/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset_builtin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:40 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/24 08:48:30 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_builtin(t_cmd *cmd_data, t_mini *mini_data)
{
	char	*key;

	key = cmd_data->cmd[1];
	if (!key_exists(mini_data->env, key))
		return ;
	delete_env_entry(mini_data->env, key);
	return ;
}
