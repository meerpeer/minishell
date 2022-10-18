/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:17 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/18 08:57:48 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(t_cmd *cmd, t_mini *data)
{
	(void) data;
	(void) cmd;
	printf("echooo 0 o 0 o :D\n");
	return ;
}
