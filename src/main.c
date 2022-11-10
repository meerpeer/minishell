/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:25:40 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/11/10 10:07:31 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include <readline/readline.h>

void	check_if_leaks_at_exit(void)
{
	printf("\n\n----\n\n");
	system("leaks -q minishell");
	printf("\n\n----\n\n");
	return ;
}

int	main(int argc, char **argv)
{
	t_mini	*mini;

	mini = init_mini_data();
	if (argc == 3)
		prompt_loop(mini, argv[2]);
	else
		prompt_loop(mini, NULL);
//	rl_replace_line();
	return (0);
}