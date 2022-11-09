/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:27 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/09 11:02:27 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * checks if all characters in the strings are numbers
 * 
 * @param str string to check
 * @return true if it's a number, false if there are other characters
*/
static bool	is_num(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * prints "exit" and exits the program if, 
 * 
 * @param cmd the exit cmd and possible exit code
*/
void	exit_builtin(char **cmd, t_mini *data)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!cmd[1])
		exit(data->exit_status);
	if (!is_num(cmd[1]))
		error_exit("exit: numeric argument required", NULL, NULL, 255);
	if (cmd[2])
	{
		print_error("exit: too many arguments", NULL, NULL);
		data->exit_status = 1;
		return ;
	}
	exit(ft_atoi(cmd[1]));
}
