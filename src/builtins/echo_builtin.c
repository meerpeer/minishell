/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merel <merel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:22:17 by mevan-de          #+#    #+#             */
/*   Updated: 2022/11/15 18:33:17 by merel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool should_add_new_line(char ***original_cmd)
{
	char	**cmd;
	char	*option;
	bool	add_newline;

	add_newline = true;
	cmd = *original_cmd;
	while (*cmd && ft_strncmp(*cmd, "-n", 2) == 0)
	{
		add_newline = false;
		option = *cmd;
		option++;
		while (option && ft_strncmp(option, "n", 1) == 0)
			option++;
		if (*option && *option != 'n')
		{
			add_newline = true;
			break ;
		}
		cmd++;
	}
	if (add_newline)
		return (true);
	*original_cmd = cmd;
	return (false);
}

void	echo_builtin(t_cmd *cmd_data)
{
	char	**cmd;
	bool	add_newline;

	add_newline = true;
	cmd = cmd_data->cmd;
	cmd++;
	add_newline = should_add_new_line(&cmd);
	while (*cmd)
	{
		printf("%s", *cmd);
		cmd++;
		if (*cmd)
			printf(" ");
	}
	if (add_newline)
		printf("\n");
}
