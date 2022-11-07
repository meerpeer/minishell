/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 07:48:55 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/07 13:09:17 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt_loop(t_mini *mini_data)
{
	while ("the world turns")
	{
		mini_data->cmd_input = readline(Y185"🐌mini🐚$ "RESET);
		if (mini_data->cmd_input == NULL)
			exit_program("something went wrong\n", 1);
		if (mini_data->cmd_input[0] != '\0')
		{
			add_history(mini_data->cmd_input);
			lexer(mini_data);
			if (try_parsing(mini_data))
				execute_cmds(mini_data);
		}
		// print_list(mini_data->token);
		// ft_lstclear(&mini_data->token, delete_token_list);
		reset_mini_data(mini_data);
	}
}
