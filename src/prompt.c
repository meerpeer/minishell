/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 07:48:55 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/10/28 11:21:03 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt_loop(t_mini *mini_data)
{
	while ("the world turns")
	{
		printf(" in prompt loop\n");
		mini_data->cmd_input = readline(Y185"🐌mini🐚$ "RESET);
		if (mini_data->cmd_input == NULL)
			exit_program("something went wrong\n", 1);
		if (mini_data->cmd_input)
			add_history(mini_data->cmd_input);
		lexer(mini_data);
		printf(G42"input[%s]\n"RESET, mini_data->cmd_input);
	}
}
