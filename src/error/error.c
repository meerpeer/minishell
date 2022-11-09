/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 09:31:41 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/09 11:05:04 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_code(t_mini *mini_data, int exit_code)
{
	exit_code = exit_code % 256;
	mini_data->exit_status = exit_code;
}

void	print_error(char *s1, char *s2, char *s3)
{
	char	*combined_string;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	combined_string = join_3_strings(s1, s2, s3);
	if (combined_string)
		ft_putstr_fd(combined_string, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

/**
	* Function that displays "minishell: +message" message and returns with
	* the errorCode. Used when error occurs in child process;
	* @param *message: a possible message to be printed after "minishell: "
	* strerror(errno) is a good option to pass to this param;
	* @param errorCode: errorCode to exit with
	* @return exit with errorCode
*/
void	error_exit(char *s1, char *s2, char *s3, int errorCode)
{
	print_error(s1, s2, s3);
	exit (errorCode);
}

void	*protect_check(void *ptr)
{
	if (ptr == NULL)
		error_exit("Memory allocation failed", NULL, NULL, 1);
	return (ptr);
}

int	exit_program(char *message, int id)
{
	if (id == 0)
	{
		ft_putstr_fd(message, 1);
		exit(0);
	}
	else if (id == 1)
	{
		ft_putstr_fd(R124"ERROR\n"RESET, 1);
		ft_putstr_fd(message, 1);
		exit(1);
	}
	return (0);
}