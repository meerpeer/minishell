/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:25:40 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/09 15:19:42 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	check_if_leaks_at_exit()
{
	printf("\n\n----\n\n");
	system("leaks -q minishell");
	printf("\n\n----\n\n");
	return ;
}

int	main()
{
	t_mini *mini;
	mini = init_mini_data();
	prompt_loop(mini);
	return (0);
}