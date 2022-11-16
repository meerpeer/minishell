/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:27 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/15 22:17:56 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "limits.h"

// bool	is_in_range(const char *str)
// {
// 	long long	i;
// 	int			n;

// 	i = 0;
// 	n = 1;
// 	while (*str == ' ' || *str == '\n' || *str == '\t'
// 		|| *str == '\v' || *str == '\f' || *str == '\r')
// 		str++;
// 	if (*str == '-' || *str == '+')
// 	{
// 		if (*str == '-' )
// 			n = n * -1;
// 		str++;
// 	}
// 	while (ft_isdigit(*str))
// 	{
// 		i = i * 10 + (*str - 48);
// 		str++;
// 	}
// 	if (i > INT_MAX)
		
// 	return ((int)i * n);
// }

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
	while (is_white_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			while (is_white_space(str[i]))
				i++;
			if (str[i] == '\0')
				return (true);
			return (false);
		}
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
//	ft_putstr_fd("exit\n", STDERR_FILENO);
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
	exit(ft_atoi(cmd[1]));
}
