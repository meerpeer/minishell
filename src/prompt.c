/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merel <merel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 07:48:55 by lhoukes           #+#    #+#             */
/*   Updated: 2022/11/02 12:12:59 by merel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt_loop(t_mini *mini_data)
{
	while ("the world turns")
	{
		printf(" in prompt loop\n");
		// mini_data->cmd_input = readline(Y185"🐌mini🐚$ "RESET);
		mini_data->cmd_input = readline(Y185"🐌mini🐚$ "RESET);
		if (mini_data->cmd_input == NULL)
			exit_program("something went wrong\n", 1);
		if (mini_data->cmd_input)
			add_history(mini_data->cmd_input);
		lexer(mini_data);
		try_parsing(mini_data);
	//	execute_cmds(mini_data);
		reset_mini_data(mini_data);
		
		
		//printf(G42"input[%s]\n"RESET, mini_data->cmd_input);
	}
}
