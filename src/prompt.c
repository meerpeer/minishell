/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 07:48:55 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/09 13:27:15 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt_loop(t_mini *mini_data)
{
	char	*input;

	while ("the world turns")
	{
		input = readline(Y185"🐌mini🐚$ "RESET);
		if (input == NULL)
			error_exit("Readline fail", NULL, NULL, 1);
		if (input)
		{
			add_history(input);
			mini_data->cmd_input = input;
			lexer(mini_data);
		//	if (try_parsing(mini_data))
		//	{
		//		print_cmds(mini_data);
		//		execute_cmds(mini_data);
		//	}
			free(input);
			reset_mini_data(mini_data);
		}
		// print_list(mini_data->token)
		
		
	}
}
