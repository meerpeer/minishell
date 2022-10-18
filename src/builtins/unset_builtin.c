/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset_builtin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 10:22:40 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/18 08:51:32 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_builtin(t_cmd *cmd, t_mini *data)
{
	(void) data;
	(void) cmd;
	printf("not set anymore ;)\n");
	return ;
}
