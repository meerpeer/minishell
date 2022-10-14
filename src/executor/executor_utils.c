/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 13:41:50 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/14 13:52:18 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd, char **builtin_names)
{
	int i;

	i = 0;
	if (!cmd || !builtin_names)
		return (false);
	while (builtin_names[i])
	{
		if (ft_strncmp(cmd, builtin_names[i]) == 0)
			return (true);
	}
	return (false);
}