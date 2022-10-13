/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 09:31:41 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/13 10:34:08 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *message, int errorCode)
{
	//char	*final_message;

	
	if (message)
		ft_putstr_fd(message, 2);
	// this is totally incomplete...
	// just make sure to create one string before using write to 
	// make it thread safe
	exit (errorCode);
}