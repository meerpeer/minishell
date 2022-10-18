/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:36 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/18 11:03:16 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

/**
	* Gets the Current Working Directory with getcwd and prints it to STDOUT
	* @param *mini_data: minishell data, used to set the exit_code;
	* @return VOID
*/
void	pwd_builtin(t_mini *mini_data)
{
	//make sure to set the error code pls
	(void)	mini_data;
	char	*pwd_str;

	pwd_str = getcwd(NULL, 0);
	if (pwd_str)
	{
		printf("%s\n", pwd_str);
		free(pwd_str);
	}
	return ;
}
