/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:36 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/18 08:51:39 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_cmd *cmd, t_mini *data)
{
	(void) data;
	(void) cmd;
	printf("pwd baby :D\n");
	return ;
}
