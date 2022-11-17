/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 07:48:55 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/17 16:47:50 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt_loop(t_mini *mini_data)
{
	char	*input;

	rl_catch_signals = 0;
	while ("the world turns")
	{
		handle_signals();
		input = readline(Y185"MINISHELL$ "RESET);
		if (input == NULL)
			exit(g_exit_status);
		if (input)
		{
			add_history(input);
			mini_data->cmd_input = input;
			lexer(mini_data);
			if (try_parsing(mini_data))
				execute_cmds(mini_data);
			ft_lstclear(&mini_data->tokens, delete_token_list);
			reset_mini_data(mini_data);
			free(input);
		}
	}
	exit (g_exit_status);
}
