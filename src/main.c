/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:25:40 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/17 16:47:43 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_mini	*mini;

	mini = init_mini_data();
	if (!mini)
		exit (1);
	prompt_loop(mini);
	return (0);
}
