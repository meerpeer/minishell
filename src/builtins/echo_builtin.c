/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:17 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/14 14:18:57 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(t_cmd *cmd_data)
{
	char	**cmd;
	bool	add_newline;

	add_newline = true;
	cmd = cmd_data->cmd;
	cmd++;
	while (*cmd && ft_strncmp(*cmd, "-n", 2) == 0)
	{
		add_newline = false;
		cmd ++;
		while (*cmd && ft_strncmp(*cmd, "n", 1) == 0)
			cmd++;
	}
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
