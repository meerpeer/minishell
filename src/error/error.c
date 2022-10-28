/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 09:31:41 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/28 11:00:00 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *s1, char *s2, char *s3)
{
	char	*combined_string;

	combined_string = join_3_strings(s1, s2, s3);
	printf("%s\n", combined_string);
}

/**
	* Function that displays "minishell: +message" message and returns with
	* the errorCode. Used when error occurs in child process;
	* @param *message: a possible message to be printed after "minishell: "
	* strerror(errno) is a good option to pass to this param;
	* @param errorCode: errorCode to exit with
	* @return exit with errorCode
*/
void	error_exit(char *message, int errorCode)
{
	//char	*final_message;

	printf("error exiting\n"); //remove this too
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (message)
		ft_putstr_fd(message, 2);
	// this is totally incomplete...
	// just make sure to create one string before using write to? or not, be fast.
	// make it thread safe
	exit (errorCode);
}

void	*protect_check(void *ptr)
{
	if (ptr == NULL)
		error_exit("memory allocation failed", 1);
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