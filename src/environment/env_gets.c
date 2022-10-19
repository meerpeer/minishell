/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_gets.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 11:43:46 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/18 11:48:10 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
	* Gets how many env variables are in env
	* @param **env: the environment variables to check;
	* @return number of variables
*/
int	get_count_env_vars(char **env)
{
	int	count;

	count = 0;
	if (!env)
		return (0);
	while (env[count])
		count++;
	return (count);
}
