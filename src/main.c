/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merel <merel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:25:40 by mevan-de          #+#    #+#             */
/*   Updated: 2022/11/03 14:45:05 by merel            ###   ########.fr       */
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
	//atexit(check_if_leaks_at_exit);
	mini = init_mini_data();
	//init_placeholder_data(mini);
	prompt_loop(mini);
	return (0);
}