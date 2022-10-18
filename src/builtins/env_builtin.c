/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:22 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/18 08:51:47 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_cmd *cmd, t_mini *data)
{
	(void) data;
	(void) cmd;
	printf("env :)\n");
	return ;
}
