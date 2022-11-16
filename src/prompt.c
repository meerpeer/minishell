/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 07:48:55 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/16 08:12:17 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt_loop(t_mini *mini_data, char *input_outside)
{
	char	*input;

	while ("the world turns")
	{
		handle_signals();
		if (input_outside) 
			input = input_outside;
		else
			input = readline(Y185"MINISHELL$ "RESET);
		if (input == NULL)
			error_exit("exit", NULL, NULL, 1);// kloptniet.nl
		if (input)
		{
			add_history(input);
			mini_data->cmd_input = input;
			lexer(mini_data);
			if (try_parsing(mini_data))
			{
				//print_cmds(mini_data);
				execute_cmds(mini_data);
			}
			ft_lstclear(&mini_data->tokens, delete_token_list);
			if (input_outside)
				exit (mini_data->exit_status);
			reset_mini_data(mini_data);
			free(input);
		}
	}
}
