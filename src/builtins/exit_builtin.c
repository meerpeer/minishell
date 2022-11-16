/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:27 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/16 13:59:47 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "limits.h"

bool	is_in_range(char *cmd, bool negative)
{
	unsigned long long	nbr;

	if (!cmd)
		return (false);
	nbr = ft_atoll(cmd);
	if ((nbr > LONG_MAX && !negative)
		|| (nbr < -(unsigned long)LONG_MIN && negative))
		return (false);
	return (true);
}

/**
 * checks if all characters in the strings are numbers
 * 
 * @param str string to check
 * @return true if it's a number, false if there are other characters
*/
static bool	is_num(char *str)
{
	int		i;
	bool	negative;

	negative = false;
	if (!str)
		return (false);
	i = 0;
	while (is_white_space(str[i]))
		i++;
	if (str[i] && str[i] == '+')
		i++;
	else if (str[i] && str[i] == '-')
	{
		i++;
		negative = true;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			while (is_white_space(str[i]))
				i++;
			if (str[i] == '\0')
				return (is_in_range(str, negative));
			return (false);
		}
		i++;
	}
	return (is_in_range(str, negative));
}

/**
 * prints "exit" and exits the program if, 
 * 
 * @param cmd the exit cmd and possible exit code
*/
void	exit_builtin(char **cmd, t_mini *data)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!cmd[1])
		exit(data->exit_status);
	if (!is_num(cmd[1]))
		error_exit("exit: ", cmd[1], ": numeric argument required", 255);
	if (cmd[2])
	{
		print_error("exit: too many arguments", NULL, NULL);
		data->exit_status = 1;
		return ;
	}
	exit(ft_atoll(cmd[1]));
}
